#pragma once
// features for zengine that can be toggled at compile time

//
// CORE FEATURES (actor and core directory)
//

// enable zengine debugging
#define _ZENGINE_DEBUG
// print initialization of actors
#undef _ZENGINE_DEBUG_INIT

//
// DEFAULT FEATURES (defaultElements)
//

// COLLIDER FEATURES

#undef _ZENGINE_COLLIDER_PERFORMANCE_EXT

// When colliding, move to position entirely before collision
#undef _ZENGINE_COLLIDER_HARD_COLLISION

// TODO: passive object system
