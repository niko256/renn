#pragma once

#include "../Core/Future.hpp"

namespace renn::future::trait {

template <SomeFuture F>
using ValueOf = F::ValueType;

}
