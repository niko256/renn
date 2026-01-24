#pragma once

#include "../Core/Future.hpp"
#include "../Thunks/Ready.hpp"
#include <algorithm>

namespace renn::future {

template <typename V>
Future<V> auto Ready(V value) {
    return thunk::Ready<V>{std::move(value)};
}

/* Synonym #1 */
template <typename V>
Future<V> auto Value(V value) {
    return Ready(std::move(value));
}

/* Synonym #2 */
template <typename V>
Future<V> auto Return(V value) {
    return Ready(std::move(value));
}

}  // namespace renn::future
