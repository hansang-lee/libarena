#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_session.hpp>
#include <catch2/catch_test_macros.hpp>

#include <atomic>
#include <iostream>
#include <thread>
#include <unordered_set>

#include "camera/api/lucid.h"

/**
 * @details
 *
 * @warning
 * please make sure at least `ONE` camera is connected, before running it.
 */

using namespace camera;

TEST_CASE("stream", "[camera/lucid]") {
    const auto system = openSystem<lucid::System>();
    REQUIRE(system != nullptr);

    std::vector<DeviceInfo> scanned;
    try {
        scanned = system->scan();
    } catch (const exception::DeviceNotFound& e) { return; } catch (const exception::GenericException& e) {
        REQUIRE(false);
    }

    std::vector<std::shared_ptr<IDevice>> devices;
    for (auto& info : scanned) {
        try {
            const auto device = system->init(info);
            devices.emplace_back(device);
        } catch (const exception::UnknownModel& e) { CHECK(false); }
    }
    REQUIRE(devices.size() > 0);
    REQUIRE(scanned.size() == devices.size());

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
        device->stream();
    }

    std::vector<std::thread> workers;
    std::atomic<int>         barrier(devices.size());

    for (const auto& device : devices) {
        workers.emplace_back([&]() {
            std::shared_ptr<camera::IImage> image;
            const std::size_t               num_samples = static_cast<std::size_t>(frame_rate * 60);
            for (std::size_t i = 0; i < num_samples; i++) {
                try {
                    image = device->capture();
                    CHECK(image != nullptr);
                    CHECK(image->complete);
                } catch (const exception::Timeout& e) { CHECK(false); }
            }
            barrier.fetch_sub(1);
        });
    }

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
}
