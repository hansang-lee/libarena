#include "camera/lucid/types.h"

#include <string>

namespace camera {
namespace lucid {
namespace utils {

[[maybe_unused]] [[nodiscard]] static camera::lucid::Model parseModel(const std::string& model_str) {
    if (model_str == "TRI028S-C") {
        return camera::lucid::Model::TRI028S_C;
    } else if (model_str == "PHX016S-C") {
        return camera::lucid::Model::PHX016S_C;
    } else if (model_str == "HTP003S-001") {
        return camera::lucid::Model::HTP003S_001;
    } else {
        return camera::lucid::Model::UNKNOWN;
    }
}

[[maybe_unused]] [[nodiscard]] static std::string parseModel(const camera::lucid::Model model) {
    switch (model) {
    case camera::lucid::Model::TRI028S_C:
        return "TRI028S-C";
    case camera::lucid::Model::PHX016S_C:
        return "PHX016S-C";
    case camera::lucid::Model::HTP003S_001:
        return "HTP003S-001";

    default:
        return "unknown";
    }
}

}  // namespace utils
}  // namespace lucid
}  // namespace camera
