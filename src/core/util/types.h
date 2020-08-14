#pragma once

#include <functional>


namespace core::util {
    template <typename Type>
    using Predicate = std::function<bool(Type)>;
}