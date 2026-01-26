#include "../../Sync/Event/Event.hpp"
#include "../Core/Future.hpp"
#include <exception>
#include <optional>

namespace renn::tryst {

template <typename T>
T get(Future<T> f) {
    std::optional<utils::Result<T>> res;
    sync::Event ready;

    f.release_state()->consume([&](utils::Result<T> r) {
        res.emplace(std::move(r));
        ready.fire();
    });

    ready.wait();

    if (res.has_value()) {
        return std::move(**res);
    } else {
        std::rethrow_exception(res->error());
    }
}

};  // namespace renn::tryst
