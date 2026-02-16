#pragma once

#include "camera/lucid/types.h"

namespace camera {
namespace lucid {

template<Model M>
struct SpecOf {};

template<>
struct SpecOf<Model::UNKNOWN> {
    static constexpr DeviceType  device_type = DeviceType::UNDEFINED;
    static constexpr std::size_t max_rate    = 0;
    static constexpr std::size_t max_width   = 0;
    static constexpr std::size_t max_height  = 0;
};

}  // namespace lucid
}  // namespace camera
