#pragma once

#include <memory>
#include <type_traits>

#include "camera/system.h"

namespace camera {

template<typename S, typename = std::enable_if_t<std::is_base_of_v<ISystem, S>>>
[[nodiscard]] std::shared_ptr<S> openSystem() {
    static std::shared_ptr<S> instance = std::make_shared<S>();
    return instance;
}

}  // namespace camera
