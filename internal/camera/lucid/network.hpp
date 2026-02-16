#pragma once

#include <ArenaApi.h>

#include <camera/exception.h>

namespace camera {
namespace lucid {
namespace network {

/**
 * @brief Configures ip address and subnet mask of the discovered entire devices.
 *
 * @param system
 */
void autoConfigureIP(Arena::ISystem* sys, std::vector<Arena::DeviceInfo>& device_infos);

}  // namespace network
}  // namespace lucid
}  // namespace camera
