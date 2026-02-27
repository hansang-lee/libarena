#pragma once

#include <cstdint>
#include <memory>

namespace camera {

struct IHeader {
    uint64_t stamp;  // nanoseconds
    uint64_t seq;
};

struct IImage {
    IHeader        header;
    std::size_t    rows  = 0;  // height
    std::size_t    cols  = 0;  // width
    std::size_t    step  = 0;
    std::size_t    depth = 0;
    const uint8_t* data  = nullptr;
};

}  // namespace camera
