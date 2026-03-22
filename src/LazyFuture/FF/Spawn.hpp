#pragma once

#include "Pure.hpp"
#include "Infra/Core/IExecutor.hpp"
#include "Via.hpp"
#include "Map.hpp"
#include <type_traits>
#include "../../Infra/Core/Env.hpp"

namespace renn::future {

template <typename F>
Future<std::invoke_result_t<F>> auto Spawn(rt::Env runtime, F func) {
    return Pure() | Via(runtime) | Map([f = std::move(func)](Unit) mutable { return f(); });
}

template <typename F>
Future<std::invoke_result_t<F>> auto Spawn(rt::IExecutor& executor, F func) {
    return Spawn(rt::Env::empty().with(executor), std::move(func));
}
}  // namespace renn::future
