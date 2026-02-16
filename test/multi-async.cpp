#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_session.hpp>
#include <catch2/catch_test_macros.hpp>

#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

#include "camera/api/lucid.h"

using namespace camera;

constexpr double ERROR_BASE_LINE = 100000.0;  // ns

TEST_CASE("multi-synced", "[camera/lucid/triton]") {
    /* initializing lucid system */
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

    for (std::size_t i = 0; i < devices.size(); i++) {
        const auto device = devices[i];

        DeviceParameters params;

        /* configuring device parameters */
        /**
         * @note when camera system sends action-commands to devices
         * to capture images at a desired future timepoint, the parameters-
         * device_key, group_key, group_mask and destination ip must be matched.
         * if not matched, unmatched devices do not respond to the action command.
         */
        params.action_device_key = 0x00000001;
        params.action_group_key  = 0x00000001;
        params.action_group_mask = 0x00000001;
        /**
         * @note for the case of lucid-vision-labs products,
         * to enable the action trigger-mode, acquisition frame rate
         * must be set to 0.
         */
        params.action_unconditional_mode         = "On";
        params.acquisition_frame_rate            = 0.0;
        params.acquisition_mode                  = "Continuous";
        params.acquisition_start_mode            = "Normal";
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
        params.pixel_format                      = "BayerRG8";
        params.ptp_enable                        = true;
        params.ptp_slave_only                    = true;
        params.reverse_x                         = false;
        params.reverse_y                         = false;
        params.stream_auto_negotiate_packet_size = false;
        params.stream_buffer_handling_mode       = "NewestOnly";
        params.stream_multicast_enable           = false;
        params.stream_packet_resend_enable       = true;
        params.target_brightness                 = 90;
        params.transfer_control_mode             = "UserControlled";
        params.transfer_operation_mode           = "Continuous";
        /**
         * @note for the case of lucid-vision-labs products,
         * to enable the action trigger-mode, the parameters below
         * must be configured.
         */
        params.trigger_activation = "RisingEdge";
        params.trigger_latency    = "Off";
        params.trigger_mode       = "On";
        params.trigger_overlap    = "PreviousFrame";
        params.trigger_selector   = "FrameStart";
        params.trigger_source     = "Action0";
        params.trigger_delay      = static_cast<double>(i * 100000.0 / devices.size());

        device->config(params);

        /* opening and streaming devices */
        device->open();
        device->stream();
    }

    bool skipped_initial_iteration = false;

    int64_t scheduled_time = std::chrono::system_clock::now().time_since_epoch().count();
    sys->fireActionCommand(scheduled_time);

    for (int i = 0; i < 500; i++) {
        sys->fireActionCommand(scheduled_time + 1e+8);
        for (std::size_t j = 0; j < devices.size(); j++) {
            const auto image = devices[j]->capture();
            if (skipped_initial_iteration) {
                CHECK(image != nullptr);
                CHECK(image->complete);
                const double dt =
                    std::abs(scheduled_time + (j * 1e+8 / devices.size()) - static_cast<int64_t>(image->header.stamp));
                CHECK(dt < ERROR_BASE_LINE);
            }
        }
        skipped_initial_iteration = true;
        scheduled_time += 1e+8;
    }

    for (const auto& device : devices) {
        device->stop();
        device->release();
    }
}
