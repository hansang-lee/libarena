#include "camera/lucid/network.hpp"
#include "camera/exception.h"

namespace camera {
namespace lucid {
namespace network {

namespace {
uint32_t generateIpAddress(uint32_t ip_address, uint32_t subnet_mask) {
    uint32_t new_ip_address(0);
    uint32_t rand_num = static_cast<uint32_t>(std::rand()) & (~subnet_mask);
    while (rand_num == 0 || rand_num == 0xFFFFFFFF || new_ip_address == 0 || new_ip_address == ip_address) {
        rand_num       = static_cast<uint32_t>(std::rand()) & (~subnet_mask);
        new_ip_address = (ip_address & subnet_mask) | rand_num;
    }
    return new_ip_address;
}

bool containDuplicate(std::vector<uint32_t>& values, const uint32_t value) {
    for (const auto& v : values) {
        if (v == value) {
            return true;
        }
    }
    return false;
}
}  // namespace

void autoConfigureIP(Arena::ISystem* sys, std::vector<Arena::DeviceInfo>& device_infos) {
    std::vector<uint32_t> ip_addrs;
    try {
        auto interface_node_map = sys->GetTLInterfaceNodeMap(device_infos[0]);
        if (!interface_node_map) {
            return;
        }

        GenApi::CIntegerPtr node_ip_addr  = interface_node_map->GetNode("GevInterfaceSubnetIPAddress");
        GenApi::CIntegerPtr node_sub_mask = interface_node_map->GetNode("GevInterfaceSubnetMask");

        // gev_sub_mask = static_cast<uint32_t>(node_sub_mask->GetValue(true, true));
        uint32_t gev_ip_addr  = static_cast<uint32_t>(node_ip_addr->GetValue());
        uint32_t gev_sub_mask = 0xffffff00;
        uint32_t gev_net_addr = gev_ip_addr & gev_sub_mask;

        ip_addrs.push_back(gev_ip_addr);

        for (auto& info : device_infos) {
            const uint32_t dev_ip_addr  = info.IpAddress();
            const uint32_t dev_sub_mask = info.SubnetMask();
            const uint32_t dev_net_addr = dev_ip_addr & dev_sub_mask;

            const auto is_new_addr_needed = ((gev_net_addr != dev_net_addr) || (gev_ip_addr == dev_ip_addr));
            if (!is_new_addr_needed) {
                ip_addrs.push_back(dev_ip_addr);
                continue;
            }

            uint64_t mac_addr    = info.MacAddress();
            uint32_t new_ip_addr = gev_ip_addr;
            while (new_ip_addr == gev_ip_addr || containDuplicate(ip_addrs, new_ip_addr)) {
                new_ip_addr = generateIpAddress(gev_ip_addr, gev_sub_mask);
            }

            ip_addrs.push_back(new_ip_addr);

            sys->ForceIp(mac_addr, new_ip_addr, gev_sub_mask, 0);
        }
    } catch (const exception::GenericException& e) { throw exception::GenericException(); }
}

}  // namespace network
}  // namespace lucid
}  // namespace camera
