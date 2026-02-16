#pragma once

#include <unordered_map>

#include "camera/interface/system.h"

namespace camera {

namespace {
template<typename S>
using is_derived_from = std::is_base_of<ISystem, S>;

template<typename S, typename = std::enable_if_t<is_derived_from<S>::value>>
std::unordered_map<std::string, std::shared_ptr<S>> systems;
}  // namespace

template<typename S, typename = std::enable_if_t<is_derived_from<S>::value>>
[[nodiscard]] std::shared_ptr<S> openSystem() {
    const std::string system_key = typeid(S).name();

    auto it = systems<S>.find(system_key);
    if (it != systems<S>.end()) {
        return it->second;
    }

    systems<S>[system_key] = std::make_shared<S>();
    return systems<S>[system_key];
}

}  // namespace camera
