#pragma once
#include <cstdint>

#include "camera/lucid/spec/common.hpp"
#include "camera/lucid/types.h"

namespace camera {
namespace lucid {

template<>
struct SpecOf<Model::HTP003S_001> {
    static constexpr DeviceType  device_type = DeviceType::TOF_CAMERA;
    static constexpr std::size_t max_rate    = 103;
    static constexpr std::size_t max_width   = 640;
    static constexpr std::size_t max_height  = 480;
};

}  // namespace lucid
}  // namespace camera
