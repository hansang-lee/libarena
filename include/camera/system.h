#pragma once

#include <ArenaApi.h>

#include <camera/device.h>

#include <vector>

namespace camera {

class ISystem {
   public:
    virtual ~ISystem() = default;

    [[nodiscard]] virtual const std::vector<DeviceInfo>  scan(const int timeout_ms)   = 0;
    [[nodiscard]] virtual const std::shared_ptr<IDevice> init(DeviceInfo device_info) = 0;

    [[nodiscard]] virtual const std::vector<std::shared_ptr<IDevice>>& devices() const { return devices_; }

    virtual void fireActionCommand(const int64_t future_time_point) = 0;
    virtual void setDeviceKey(const int64_t device_key)             = 0;
    virtual void setGroupKey(const int64_t group_key)               = 0;
    virtual void setGroupMask(const int64_t group_mask)             = 0;
    virtual void setTargetIp(const int64_t target_ip)               = 0;

   protected:
    std::vector<std::shared_ptr<IDevice>> devices_;
};

}  // namespace camera
