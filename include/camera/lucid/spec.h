#pragma once

#include <cstddef>

#include "camera/lucid/types.h"

namespace camera {
namespace lucid {

struct Spec {
    DeviceType  device_type;
    std::size_t max_rate;
    std::size_t max_width;
    std::size_t max_height;
};

Spec specOf(Model model);

}  // namespace lucid
}  // namespace camera
