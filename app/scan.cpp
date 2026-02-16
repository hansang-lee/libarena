#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>

#include "camera/api/lucid.h"

int main() {
    std::vector<camera::DeviceInfo> checked;

    const auto contains = [&](const camera::DeviceInfo& item) {
        return std::any_of(checked.begin(), checked.end(), [&](const auto& i) { return i.serial == item.serial; });
    };

    const auto system = camera::openSystem<camera::lucid::System>();
    const auto start  = std::chrono::steady_clock::now();

    while (std::chrono::steady_clock::now() - start < std::chrono::seconds{10}) {
        const auto scanned = system->scan();
        for (const auto& item : scanned) {
            if (contains(item)) {
                continue;
            }
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
            checked.emplace_back(item);
        }
    }

    return 0;
}
