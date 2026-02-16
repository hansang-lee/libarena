#include <stdexcept>

#include "camera/exception.h"
#include "camera/lucid/spec.h"
#include "camera/lucid/spec.hpp"

namespace camera {
namespace lucid {

namespace {

template<Model M>
constexpr Spec defineRuntimeSpec() {
    using S = SpecOf<M>;
    return Spec{
        S::device_type,
        S::max_rate,
        S::max_width,
        S::max_height,
    };
}

const Spec UNKNOWN     = defineRuntimeSpec<Model::UNKNOWN>();
const Spec TRI028S_C   = defineRuntimeSpec<Model::TRI028S_C>();
const Spec PHX016S_C   = defineRuntimeSpec<Model::PHX016S_C>();
const Spec HTP003S_001 = defineRuntimeSpec<Model::HTP003S_001>();

}  // namespace

Spec specOf(Model model) {
    switch (model) {
    case Model::UNKNOWN:
        return UNKNOWN;
    case Model::TRI028S_C:
        return TRI028S_C;
    case Model::PHX016S_C:
        return PHX016S_C;
    case Model::HTP003S_001:
        return HTP003S_001;
    default:
        return UNKNOWN;
    }
}

}  // namespace lucid
}  // namespace camera
