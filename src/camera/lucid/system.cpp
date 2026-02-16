#include <algorithm>

#include "camera/lucid/network.hpp"
#include "camera/lucid/system.hpp"

#include "camera/lucid/utils/model.h"

namespace camera {
namespace lucid {

System::System() {
    try {
        arena_system_   = Arena::OpenSystem();
        arena_node_map_ = arena_system_->GetTLSystemNodeMap();
    } catch (const GenICam::GenericException& e) { throw exception::GenericException(e.what()); }

    setDeviceKey(0x00000001);
    setGroupKey(0x00000001);
    setGroupMask(0x00000001);
    setTargetIp(0xFFFFFFFF);
}

System::~System() {
    if (arena_system_ != nullptr) {
        // for (auto& device : devices_) {
        //     device->stop();
        //     device->release();
        //     device = nullptr;
        // }
        try {
            Arena::CloseSystem(arena_system_);
        } catch (const GenICam::GenericException& e) { std::cerr << e.what() << std::endl; }
    }
}

const std::shared_ptr<IDevice> System::init(DeviceInfo device_info) {
    std::shared_ptr<IDevice> device;
    try {
        device = updateDevice_(device_info);
    } catch (const exception::UnknownModel& e) { throw exception::UnknownModel(); }

    return device;
}

const std::vector<DeviceInfo> System::scan(const int timeout_ms) {
    try {
        arena_system_->UpdateDevices(timeout_ms);
        last_scanned_devices_info_ = arena_system_->GetDevices();
    } catch (const GenICam::GenericException& e) { throw exception::GenericException(e.what()); }

    if (last_scanned_devices_info_.empty()) {
        throw exception::DeviceNotFound();
    }

    removeDuplicate_(last_scanned_devices_info_);

    std::vector<DeviceInfo> devices_info;
    for (auto info : last_scanned_devices_info_) {
        DeviceInfo t_device_info;
        t_device_info.device_version        = std::string(info.DeviceVersion().c_str());
        t_device_info.model                 = std::string(info.ModelName().c_str());
        t_device_info.serial                = std::string(info.SerialNumber().c_str());
        t_device_info.vendor                = std::string(info.VendorName().c_str());
        t_device_info.mac                   = std::string(info.MacAddressStr().c_str());
        t_device_info.ipv4                  = std::string(info.IpAddressStr().c_str());
        t_device_info.subnet_mask           = std::string(info.SubnetMaskStr().c_str());
        t_device_info.gateway               = std::string(info.DefaultGatewayStr().c_str());
        t_device_info.persistent_ip_enabled = info.IsPersistentIpConfigurationEnabled();
        t_device_info.dhcp_enabled          = info.IsDHCPConfigurationEnabled();
        t_device_info.lla_enabled           = info.IsLLAConfigurationEnabled();
        devices_info.emplace_back(t_device_info);
    }

    return devices_info;
}

void System::fireActionCommand(const int64_t future_time_point) {
    try {
        Arena::SetNodeValue(arena_system_->GetTLSystemNodeMap(), "ActionCommandExecuteTime", future_time_point);
        Arena::ExecuteNode(arena_system_->GetTLSystemNodeMap(), "ActionCommandFireCommand");
    } catch (const GenICam::GenericException& e) { throw exception::GenericException(e.what()); }
}

void System::setDeviceKey(const int64_t device_key) {
    try {
        Arena::SetNodeValue<int64_t>(arena_node_map_, "ActionCommandDeviceKey", device_key);
    } catch (const GenICam::GenericException& e) { throw exception::GenericException(e.what()); }
}

void System::setGroupKey(const int64_t group_key) {
    try {
        Arena::SetNodeValue<int64_t>(arena_node_map_, "ActionCommandGroupKey", group_key);
    } catch (const GenICam::GenericException& e) { throw exception::GenericException(e.what()); }
}

void System::setGroupMask(const int64_t group_mask) {
    try {
        Arena::SetNodeValue<int64_t>(arena_node_map_, "ActionCommandGroupMask", group_mask);
    } catch (const GenICam::GenericException& e) { throw exception::GenericException(e.what()); }
}

void System::setTargetIp(const int64_t target_ip) {
    try {
        Arena::SetNodeValue<int64_t>(arena_node_map_, "ActionCommandTargetIP", target_ip);
    } catch (const GenICam::GenericException& e) { throw exception::GenericException(e.what()); }
}

bool System::IsDeviceModelSupported(DeviceInfo device_info) {
    return (utils::parseModel(device_info.model) != Model::UNKNOWN);
}

void System::configureAddressIpAuto(std::vector<DeviceInfo> devices_info) {
    if (arena_system_ == nullptr) {
        return;  // system is not initialized
    }
    std::vector<Arena::DeviceInfo> matched;
    for (auto arena_device_info : last_scanned_devices_info_) {
        const auto serial = std::string(arena_device_info.SerialNumber().c_str());
        for (auto device_info : devices_info) {
            if (device_info.serial != serial) {
                continue;
            }
            matched.emplace_back(arena_device_info);
            break;
        }
    }
    try {
        network::autoConfigureIP(arena_system_, matched);
        arena_system_->UpdateDevices(1000);
    } catch (const exception::GenericException& e) { throw exception::GenericException(); }
}

void System::configureAddressIpAuto(DeviceInfo device_info) {
    if (arena_system_ == nullptr) {
        return;  // system is not initialized
    }
    Arena::DeviceInfo matched;
    for (auto arena_device_info : last_scanned_devices_info_) {
        const auto serial = std::string(arena_device_info.SerialNumber().c_str());
        if (device_info.serial != serial) {
            continue;  // not matched
        }
        try {
            std::vector<Arena::DeviceInfo> _info;
            _info.push_back(arena_device_info);
            network::autoConfigureIP(arena_system_, _info);
            arena_system_->UpdateDevices(1000);
        } catch (const exception::GenericException& e) { throw exception::GenericException(); }
        break;
    }
}

void System::removeDuplicate_(std::vector<Arena::DeviceInfo>& arena_device_info) {
    std::sort(arena_device_info.begin(), arena_device_info.end(),
              [](Arena::DeviceInfo& a, Arena::DeviceInfo& b) { return a.SerialNumber() < b.SerialNumber(); });
    std::vector<Arena::DeviceInfo> filtered;
    for (auto& info : arena_device_info) {
        if (filtered.empty() || filtered.back().SerialNumber() != info.SerialNumber()) {
            filtered.push_back(info);
        }
    }
    arena_device_info.clear();
    arena_device_info = std::vector<Arena::DeviceInfo>(filtered.begin(), filtered.end());
}

std::shared_ptr<IDevice> System::updateDevice_(DeviceInfo device_info) {
    for (auto arena_device_info : last_scanned_devices_info_) {
        const std::string serial = std::string(arena_device_info.SerialNumber().c_str());
        if (device_info.serial != serial) {
            continue;
        }
        return createDevice_(arena_device_info);
    }
    return nullptr;
}

std::shared_ptr<IDevice> System::createDevice_(Arena::DeviceInfo arena_device_info) {
    DeviceInfo device_info;
    device_info.model          = std::string(arena_device_info.ModelName().c_str());
    device_info.device_version = std::string(arena_device_info.DeviceVersion().c_str());
    device_info.serial         = std::string(arena_device_info.SerialNumber().c_str());
    device_info.vendor         = std::string(arena_device_info.VendorName().c_str());
    device_info.mac            = std::string(arena_device_info.MacAddressStr().c_str());
    device_info.ipv4           = std::string(arena_device_info.IpAddressStr().c_str());
    device_info.subnet_mask    = std::string(arena_device_info.SubnetMaskStr().c_str());
    device_info.gateway        = std::string(arena_device_info.DefaultGatewayStr().c_str());

    device_info.persistent_ip_enabled = arena_device_info.IsPersistentIpConfigurationEnabled();
    device_info.dhcp_enabled          = arena_device_info.IsDHCPConfigurationEnabled();
    device_info.lla_enabled           = arena_device_info.IsLLAConfigurationEnabled();

    const auto spec = specOf(utils::parseModel(device_info.model));
    if (spec.device_type == DeviceType::UNDEFINED) {  // found unsupported model
        throw exception::UnknownModel();
    }

    device_info.device_type = spec.device_type;
    device_info.max_width   = spec.max_width;
    device_info.max_height  = spec.max_height;
    device_info.rate        = spec.max_rate;

    return std::make_shared<Device>(arena_system_, arena_device_info, device_info);
}

}  // namespace lucid
}  // namespace camera
