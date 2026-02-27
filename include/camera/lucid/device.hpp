#pragma once

#include <ArenaApi.h>

#include "camera/device.h"
#include "camera/lucid/config.hpp"

#include <atomic>
#include <memory>
#include <vector>

namespace camera {
namespace lucid {

class Device: public IDevice {
   public:
    Device(Arena::ISystem* system, Arena::DeviceInfo arena_info, DeviceInfo custom_info);
    virtual ~Device() override;

    void config(const DeviceParameters& param) override;
    void open() override;
    void release() override;
    void stream(const std::size_t num_buffer = 5UL) override;
    void stop() override;

    bool isConnected() override;
    bool isAvailable() override;

    [[nodiscard]] std::shared_ptr<IImage> capture(const int64_t timeout_ms = 1000UL) override;

    void configurePersistentIpAddress(const std::string& ipv4, const std::string& subnet) override;

    [[nodiscard]] std::shared_ptr<Config> config() const { return config_; }

   private:
    Arena::ISystem*   arena_system_ = nullptr;
    Arena::IDevice*   arena_device_ = nullptr;
    Arena::DeviceInfo arena_info_;

    std::shared_ptr<Config> config_ = nullptr;
    DeviceParameters        param_;

    std::atomic<bool> is_available_to_capture_{false};

    void applyParamsOnDevice_();
};

}  // namespace lucid
}  // namespace camera
