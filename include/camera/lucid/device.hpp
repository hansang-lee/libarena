#pragma once

#include <ArenaApi.h>

#include <atomic>
#include <cassert>
#include <cstdint>
#include <filesystem>

#include <camera/exception.h>

#include <camera/device.h>
#include <camera/image.h>
#include <camera/system.h>

#include <camera/lucid/config.hpp>

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

    void configurePersistentIpAddress(const std::string& ipv4, const std::string& subnet);

   private:
    void applyParamsOnDevice_();

    Arena::ISystem*         arena_system_ = nullptr;
    Arena::IDevice*         arena_device_ = nullptr;
    Arena::DeviceInfo       arena_info_;
    std::shared_ptr<Config> config_ = nullptr;
    DeviceParameters        param_;
    std::atomic<bool>       is_available_to_capture_;
};

}  // namespace lucid
}  // namespace camera
