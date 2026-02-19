#include <fstream>
#include <thread>

#include <arpa/inet.h>

#include "camera/lucid/device.hpp"
#include "camera/lucid/network.hpp"
#include "camera/lucid/types.h"

#include "camera/lucid/utils.h"

namespace camera {
namespace lucid {

namespace {
int64_t toIntIPAddress(const std::string& ip_address) {
    struct in_addr ip_addr;
    return (inet_aton(ip_address.c_str(), &ip_addr) == 0) ? (-1) : ntohl(ip_addr.s_addr);
}
}  // namespace

Device::Device(Arena::ISystem* system, Arena::DeviceInfo arena_info, DeviceInfo custom_info)
    : arena_system_(system)
    , arena_info_(arena_info)
    , is_available_to_capture_(false) {
    info_ = std::move(custom_info);
}

Device::~Device() {}

void Device::config(const DeviceParameters& param) {
    param_ = param;
}

void Device::open() {
    try {
        arena_device_ = arena_system_->CreateDevice(arena_info_);
        config_       = std::make_shared<Config>(arena_system_, arena_device_);
        if (config_->getDeviceAccessStatus() == "ReadWrite") {
            applyParamsOnDevice_();
        }
        info_.rate = config_->getAcquisitionFrameRate();
    } catch (const GenICam::AccessException& e) {
        throw exception::DevicecNotAccesible();
    } catch (const GenICam::GenericException& e) { throw exception::GenericException(e.what()); }
}

void Device::release() {
    try {
        arena_system_->DestroyDevice(arena_device_);
    } catch (const GenICam::GenericException& e) { throw exception::GenericException(e.what()); }
    arena_device_ = nullptr;
}

void Device::stream(const std::size_t num_buffer) {
    try {
        if (info_.device_type == DeviceType::RGB_CAMERA) {
            Arena::ExecuteNode(arena_device_->GetNodeMap(), "TransferStart");
        }
        arena_device_->StartStream(num_buffer);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        is_available_to_capture_.store(true);
    } catch (const GenICam::GenericException& e) { throw exception::GenericException(e.what()); }
}

void Device::stop() {
    try {
        is_available_to_capture_.store(false);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        arena_device_->StopStream();
        if (info_.device_type == DeviceType::RGB_CAMERA) {
            Arena::ExecuteNode(arena_device_->GetNodeMap(), "TransferStop");
        }
    } catch (const GenICam::GenericException& e) { throw exception::GenericException(e.what()); }
}

bool Device::isConnected() {
    return arena_device_->IsConnected();
}

bool Device::isAvailable() {
    return is_available_to_capture_.load();
}

std::shared_ptr<IImage> Device::capture(const int64_t timeout_ms) {
    try {
        const auto                 image = arena_device_->GetImage(timeout_ms);
        std::unique_ptr<uint8_t[]> data(new uint8_t[image->GetSizeFilled()]);
        std::memcpy(data.get(), image->GetData(), image->GetSizeFilled());
#if __cplusplus > 201703L  // c++20 or later
        std::shared_ptr<IImage> result = std::make_shared<IImage>(IImage{
            .complete = (image->GetSizeFilled() == image->GetPayloadSize()),
            .header   = IHeader{.stamp = image->GetTimestamp(), .seq = image->GetFrameId()},
            .rows     = image->GetHeight(),
            .cols     = image->GetWidth(),
            .step     = (image->GetSizeFilled() / image->GetHeight()),
            .depth    = image->GetBitsPerPixel(),
            .data     = std::move(data),
        });
#elif __cplusplus <= 201703L  // c++17 or earlier
        std::shared_ptr<IImage> result = std::make_shared<IImage>();
        result->complete               = (image->GetSizeFilled() == image->GetPayloadSize());
        result->header.stamp           = image->GetTimestamp();
        result->header.seq             = image->GetFrameId();
        result->rows                   = image->GetHeight();
        result->cols                   = image->GetWidth();
        result->step                   = (image->GetSizeFilled() / image->GetHeight());
        result->depth                  = image->GetBitsPerPixel();
        result->data                   = std::move(data);
#else
        throw std::runtime_error("Unsupported C++ Standard Version");
#endif
        arena_device_->RequeueBuffer(image);
        return result;
    } catch (const GenICam::TimeoutException& e) {
        throw exception::Timeout();
    } catch (const GenICam::GenericException& e) { throw exception::GenericException(e.what()); }
}

void Device::configurePersistentIpAddress(const std::string& ipv4, const std::string& subnet) {
    arena_system_->ForceIp(arena_info_.MacAddress(), toIntIPAddress(ipv4), toIntIPAddress(subnet), 0);

    config_->setGevPersistentIPAddress(ipv4.c_str());
    config_->setGevPersistentSubnetMask(subnet.c_str());
    config_->setGevCurrentIPConfigurationPersistentIP(true);
    config_->setGevCurrentIPConfigurationDHCP(false);
    config_->setGevPersistentARPConflictDetectionEnable(false);
}

void Device::applyParamsOnDevice_() {
    try {
        config_->setActionDeviceKey(param_.action_device_key);
        config_->setActionGroupKey(param_.action_group_key);
        config_->setActionGroupMask(param_.action_group_mask);
        config_->setActionSelector(param_.action_selector);
        config_->setActionUnconditionalMode(param_.action_unconditional_mode.c_str());

        config_->setAcquisitionMode(param_.acquisition_mode.c_str());
        config_->setAcquisitionStartMode(param_.acquisition_start_mode.c_str());

        config_->setBinningSelector(param_.binning_selector.c_str());
        if (config_->getBinningSelector() == "Digital") {
            config_->setBinningHorizontal(param_.binning_horizontal);
            config_->setBinningHorizontalMode(param_.binning_horizontal_mode.c_str());
            config_->setBinningVertical(param_.binning_vertical);
            config_->setBinningVerticalMode(param_.binning_vertical_mode.c_str());
        }

        config_->setGainAuto(param_.gain_auto.c_str());
        config_->setGevSCDA(param_.gev_scda.c_str());

        if (param_.gev_current_ip_configuration_dhcp) {
            config_->setGevCurrentIPConfigurationDHCP(true);
            config_->setGevCurrentIPConfigurationPersistentIP(false);
        }

        const auto max_w = config_->getWidthMax();
        const auto w     = ((param_.width <= 0) || (param_.width >= max_w)) ? max_w : param_.width;
        config_->setWidth(w);

        const auto max_h = config_->getHeightMax();
        const auto h     = ((param_.height <= 0) || (param_.height >= max_h)) ? max_h : param_.height;
        config_->setHeight(h);

        config_->setPixelFormat(param_.pixel_format.c_str());
        config_->setPtpEnable(param_.ptp_enable);
        config_->setPtpSlaveOnly(param_.ptp_slave_only);

        config_->setStreamAutoNegotiatePacketSize(param_.stream_auto_negotiate_packet_size);
        config_->setStreamBufferHandlingMode(param_.stream_buffer_handling_mode.c_str());
        config_->setStreamMulticastEnable(param_.stream_multicast_enable);
        config_->setStreamPacketResendEnable(param_.stream_packet_resend_enable);
        config_->setTransferControlMode(param_.transfer_control_mode.c_str());
        config_->setTransferSelector("Stream0");

        config_->setTriggerMode(param_.trigger_mode.c_str());
        if (config_->getTriggerMode() == "On") {
            config_->setTriggerActivation(param_.trigger_activation.c_str());
            config_->setTriggerDelay(param_.trigger_delay);
            config_->setTriggerOverlap(param_.trigger_overlap.c_str());
            if (config_->getTriggerOverlap() == "Off") {
                config_->setTriggerLatency(param_.trigger_latency.c_str());
            }
            config_->setTriggerSelector(param_.trigger_selector.c_str());
            config_->setTriggerSource(param_.trigger_source.c_str());
        }

        const bool enable_rate = ((param_.acquisition_frame_rate > 0.0) && (config_->getTriggerMode() != "On"));
        config_->setAcquisitionFrameRateEnable(enable_rate);
        if (config_->getAcquisitionFrameRateEnable()) {
            config_->setAcquisitionFrameRate(param_.acquisition_frame_rate);
        }

        switch (info_.device_type) {
        case DeviceType::RGB_CAMERA:
            config_->setExposureAuto(param_.exposure_auto.c_str());
            if (config_->getExposureAuto() == "Continuous") {
                config_->setExposureAutoLimitAuto(param_.exposure_auto_limit_auto.c_str());
                if ((config_->getExposureAutoLimitAuto()) == "Off") {
                    config_->setExposureAutoLowerLimit(param_.exposure_auto_lower_limit);
                    config_->setExposureAutoUpperLimit(param_.exposure_auto_upper_limit);
                }
            } else if (config_->getExposureAuto() == "Off") {
                config_->setExposureTime(param_.exposure_time);
            }

            config_->setReverseX(param_.reverse_x);
            config_->setReverseY(param_.reverse_y);

            config_->setTargetBrightness(param_.target_brightness);
            config_->setTransferOperationMode(param_.transfer_operation_mode.c_str());
            break;
        case DeviceType::TOF_CAMERA:
            config_->setScan3dModeSelector("Processed");
            config_->setConversionGain(param_.conversion_gain.c_str());
            break;

        default:
            break;
        }
    } catch (const GenICam::GenericException& e) { throw exception::GenericException(e.what()); }
}

}  // namespace lucid
}  // namespace camera
