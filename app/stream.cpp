#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

#include "camera/api/lucid.h"

int main() {
    const auto system  = camera::openSystem<camera::lucid::System>();
    const auto scanned = system->scan();

    std::vector<std::shared_ptr<camera::IDevice>> devices;

    for (const auto& item : scanned) {
        // clang-format off
        std::clog
            << item.mac << " [S/N: " << item.serial << "]"
            << "\033[90m"
            << "\n- IP            : " << item.ipv4
            << "\n- Subnet Mask   : " << item.subnet_mask
            << "\n- Gateway       : " << item.gateway
            << "\n- DHCP Enabled  : " << item.dhcp_enabled
            << "\n- Persistent IP : " << item.persistent_ip_enabled
            << "\n- LLA Enabled   : " << item.lla_enabled
            << "\033[0m"
            << std::endl;
        // clang-format on

        try {
            devices.emplace_back(system->init(item));
        } catch (const camera::exception::UnknownModel& e) { continue; }
    }

    if (devices.empty()) {
        return 1;
    }

    for (std::size_t i = 0; i < devices.size(); i++) {
        const auto device = devices[i];

        camera::DeviceParameters params;
        params.action_unconditional_mode         = "On";
        params.acquisition_frame_rate            = 30.0;
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
        params.pixel_format                      = "BayerRG8";
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
    }

    for (const auto device : devices) {
        device->stream();
    }

    std::vector<std::thread> workers;
    std::atomic<int>         barrier(devices.size());
    std::atomic<bool>        stop_requested(false);

    for (const auto& device : devices) {
        workers.emplace_back([&]() {
            while (!stop_requested.load()) {
                try {
                    const auto image = device->capture();
                    if (!image->complete) {
                        break;
                    }
                } catch (const camera::exception::Timeout& e) { std::cerr << e.what() << std::endl; }
            }
            barrier.fetch_sub(1);
        });
    }

    std::cin.get();

    stop_requested.store(true);

    while (barrier.load() != 0) {
        std::this_thread::sleep_for(std::chrono::microseconds(100));
    }

    for (const auto& device : devices) {
        device->stop();
        device->release();
    }

    for (auto& worker : workers) {
        worker.join();
    }

    return 0;
}
