#pragma once

#include "../../Utils/Routine.hpp"
#include "Core/Env.hpp"

namespace renn::fiber {

void go(rt::Env, utils::Routine);

void go(utils::Routine);

};  // namespace renn::fiber
