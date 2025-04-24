#pragma once

#include <memory>
#include <raylib.h>

#define NewUnique(type) std::make_unique<type>()
#define Unique(type) std::unique_ptr<type>
#define Shared(type) std::shared_ptr<type>
#define NewShared(type) std::make_shared<type>()
