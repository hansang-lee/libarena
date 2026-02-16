#pragma once
#include <cstdint>

#include "camera/lucid/spec/common.hpp"
#include "camera/lucid/types.h"

namespace camera {
namespace lucid {

template<>
struct SpecOf<Model::TRI028S_C> {
    static constexpr DeviceType  device_type = DeviceType::RGB_CAMERA;
    static constexpr std::size_t max_rate    = 39;
    static constexpr std::size_t max_width   = 1936;
    static constexpr std::size_t max_height  = 1464;
};

}  // namespace lucid
}  // namespace camera
