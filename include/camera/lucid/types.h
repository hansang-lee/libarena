#pragma once

namespace camera {

enum DeviceType
{
    UNDEFINED  = 0,
    RGB_CAMERA = 1,
    TOF_CAMERA = 2,
};

namespace lucid {

/**
 * @brief Lucid camera model name.
 */
enum class Model
{
    UNKNOWN,
    TRI028S_C,
    PHX016S_C,
    HTP003S_001,
};

}  // namespace lucid
}  // namespace camera
