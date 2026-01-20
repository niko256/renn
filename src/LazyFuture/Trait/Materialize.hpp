#pragma once

#include "../Core/Continuation.hpp"
#include "../Core/Future.hpp"
#include "ValueOf.hpp"
#include <utility>

namespace renn::future::trait {

template <SomeFuture F, Continuation<ValueOf<F>> Consumer>
using Materialize = decltype(std::declval<F>().materialize(std::declval<Consumer>()));

}
