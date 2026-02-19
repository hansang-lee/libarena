#pragma once

#include <cstdint>
#include <memory>
#include <vector>

namespace camera {

struct IHeader {
    uint64_t stamp;  // nanoseconds
    uint64_t seq;
};

struct IImage {
    bool                       complete = false;
    IHeader                    header;
    std::size_t                rows  = 0;  // height
    std::size_t                cols  = 0;  // width
    std::size_t                step  = 0;
    std::size_t                depth = 0;
    std::unique_ptr<uint8_t[]> data;
};

}  // namespace camera
