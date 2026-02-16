#pragma once
#include <cstdint>

#include "camera/lucid/spec/common.hpp"
#include "camera/lucid/types.h"

namespace camera {
namespace lucid {

template<>
struct SpecOf<Model::PHX016S_C> {
    static constexpr DeviceType  device_type = DeviceType::RGB_CAMERA;
    static constexpr std::size_t max_rate    = 71;
    static constexpr std::size_t max_width   = 1440;
    static constexpr std::size_t max_height  = 1080;
};

}  // namespace lucid
}  // namespace camera
