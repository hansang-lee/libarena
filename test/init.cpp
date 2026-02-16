#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_session.hpp>
#include <catch2/catch_test_macros.hpp>

#include <unordered_set>

#include "camera/api/lucid.h"

/**
 * @details
 * it tests the initialization of a camera system using the Lucid-Vision-Labs `Triton` camera.
 * the test ensures that the camera system initializes successfully, and that the system contains at least one connected device.
 * it also checks that each device in the system contains unique info, such as MAC address, IPv4 address and serial number, as well as general device info.
 *
 * @warning
 * please make sure at least `ONE` camera is connected, before running it.
 */

using namespace camera;

namespace {
/**
 * @note std::unordered_set supports `contains` function from c++20.
 * therefore `contains` function is implemented below.
 */
template<typename T>
class unordered_set_: public std::unordered_set<T> {
   public:
    unordered_set_()
        : std::unordered_set<T>() {}

    [[nodiscard]] bool contains(const T& value) const { return this->find(value) != this->end(); }
};
}  // namespace

TEST_CASE("init", "[camera/lucid/triton]") {
    const auto sys = openSystem<lucid::System>();
    REQUIRE(sys != nullptr);

    std::vector<DeviceInfo> scanned;
    try {
        scanned = sys->scan();
    } catch (const exception::DeviceNotFound& e) { return; } catch (const exception::GenericException& e) {
        REQUIRE(false);
    }

    std::vector<std::shared_ptr<IDevice>> devices;
    for (auto& info : scanned) {
        try {
            const auto device = sys->init(info);
            devices.emplace_back(device);
        } catch (const exception::UnknownModel& e) { CHECK(false); }
    }
    REQUIRE(devices.size() > 0);
    REQUIRE(scanned.size() == devices.size());

    unordered_set_<std::string> macs;
    unordered_set_<std::string> ipv4s;
    unordered_set_<std::string> serials;

    const double frame_rate = 10.0;

    for (std::size_t i = 0; i < devices.size(); i++) {
        const auto device = devices[i];

        DeviceParameters params;
        params.action_unconditional_mode         = "On";
        params.acquisition_frame_rate            = frame_rate;
        params.acquisition_mode                  = "Continuous";
        params.acquisition_start_mode            = "LowLatency";
        params.binning_horizontal                = 1;
        params.binning_horizontal_mode           = "Average";
        params.binning_selector                  = "Digital";
        params.binning_vertical                  = 1;
        params.binning_vertical_mode             = "Average";
        params.exposure_auto                     = "Continuous";
        params.exposure_auto_limit_auto          = "Off";
        params.exposure_auto_lower_limit         = 30.0;
        params.exposure_auto_upper_limit         = 2500.0;
        params.exposure_time                     = 500.0;
        params.gev_current_ip_configuration_dhcp = scanned[i].persistent_ip_enabled ? false : true;
        params.persistent_ip_enable              = scanned[i].persistent_ip_enabled ? true : false;
        params.gain_auto                         = "Continuous";
        params.pixel_format                      = "BGR8";
        params.ptp_enable                        = true;
        params.ptp_slave_only                    = true;
        params.reverse_x                         = false;
        params.reverse_y                         = false;
        params.stream_auto_negotiate_packet_size = false;
        params.stream_buffer_handling_mode       = "OldestFirstOverwrite";
        params.stream_multicast_enable           = false;
        params.stream_packet_resend_enable       = true;
        params.target_brightness                 = 90;
        params.transfer_control_mode             = "UserControlled";
        params.transfer_operation_mode           = "Continuous";
        params.trigger_activation                = "RisingEdge";
        params.trigger_latency                   = "Off";
        params.trigger_mode                      = "Off";
        params.trigger_overlap                   = "Off";
        params.trigger_selector                  = "FrameStart";
        params.trigger_source                    = "Action0";

        device->config(params);
        device->open();

        const auto info = device->info();

        CHECK(info.vendor == "Lucid Vision Labs");
        CHECK(!info.device_version.empty());
        CHECK(std::stoi(info.serial) > 0);
        CHECK(info.mac.size() == 17);
        CHECK(7 <= info.ipv4.size());
        CHECK(info.ipv4.size() <= 15);
        CHECK(static_cast<int>(info.rate) == frame_rate);
        CHECK(info.max_width > 0);
        CHECK(info.max_height > 0);

        if (!macs.contains(info.mac)) {
            macs.insert(info.mac);
        }
        if (!ipv4s.contains(info.ipv4)) {
            ipv4s.insert(info.ipv4);
        }
        if (!serials.contains(info.serial)) {
            serials.insert(info.serial);
        }

        device->release();
    }

    /**
     * @remark
     * it checks redundancy over `mac-addrs`, `ipv4-addrs` and `serial numbers`.
     */
    REQUIRE(macs.size() == devices.size());
    REQUIRE(ipv4s.size() == devices.size());
    REQUIRE(serials.size() == devices.size());
}
