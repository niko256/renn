#pragma once

#include "../Continuation/Continuation.hpp"
#include "../Core/Thunk.hpp"
#include "ValueOf.hpp"
#include <utility>

namespace renn::future::trait {

template <thunk::Thunk TH, Continuation<ValueOf<TH>> Downstream>
using ComputationOf
    = decltype(std::declval<TH>().materialize(std::declval<Downstream>()));
}
