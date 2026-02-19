#include <algorithm>
#include <cctype>
#include <iostream>

#include "camera/api/lucid.h"

int main() {
    const auto system = camera::openSystem<camera::lucid::System>();

    std::vector<camera::DeviceInfo> scanned;
    try {
        scanned = system->scan();
    } catch (const camera::exception::DeviceNotFound& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    } catch (const camera::exception::GenericException& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    if (scanned.empty()) {
        std::cerr << "No device found" << std::endl;
        return -1;
    }

    system->configureAddressIpAuto(scanned);

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
    }

    return 0;
}
