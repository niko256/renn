#pragma once

#include "../../Infra/Core/IExecutor.hpp"
#include "../../Utils/Routine.hpp"

namespace renn::fiber {

void go(rt::IExecutor&, utils::Routine);

void go(utils::Routine);

};  // namespace renn::fiber
