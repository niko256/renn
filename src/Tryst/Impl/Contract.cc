#include "../Core/Future.hpp"
#include "../Core/Promise.hpp"
#include <tuple>

namespace renn::tryst {

template <typename T>
std::tuple<Future<T>, Promise<T>> contract() {
    auto state = new SharedState<T>;

    auto future = Future<T>{state};
    auto promise = Promise<T>{state};

    return std::make_tuple(std::move(future), std::move(promise));
}

};  // namespace renn::tryst
