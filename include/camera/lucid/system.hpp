#pragma once

#include <ArenaApi.h>

#include "camera/device.h"
#include "camera/system.h"

#include "camera/lucid/device.hpp"
#include "camera/lucid/spec.h"

#include <cstdint>
#include <string>
#include <vector>

namespace camera {
namespace lucid {

class System: public ISystem {
   public:
    System();
    virtual ~System() override;

    const std::shared_ptr<IDevice> init(DeviceInfo device_info) override;
    const std::vector<DeviceInfo>  scan(const int timeout_ms = 1000) override;

    void fireActionCommand(const int64_t future_time_point) override;
    void setDeviceKey(const int64_t device_key) override;
    void setGroupKey(const int64_t group_key) override;
    void setGroupMask(const int64_t group_mask) override;
    void setTargetIp(const int64_t target_ip) override;

    bool IsDeviceModelSupported(DeviceInfo device_info);
    void configureAddressIpAuto(std::vector<DeviceInfo> devices_info);
    void configureAddressIpAuto(DeviceInfo device_info);

   private:
    Arena::ISystem*   arena_system_   = nullptr;
    GenApi::INodeMap* arena_node_map_ = nullptr;

    std::vector<Arena::DeviceInfo> last_scanned_devices_info_;

    void                     removeDuplicate_(std::vector<Arena::DeviceInfo>& arena_device_info);
    std::shared_ptr<IDevice> updateDevice_(DeviceInfo device_info);
    std::shared_ptr<IDevice> createDevice_(Arena::DeviceInfo arena_device_info);
};

}  // namespace lucid
}  // namespace camera
