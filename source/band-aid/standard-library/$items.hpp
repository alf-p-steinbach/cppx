// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
#pragma once
#include <stdlib/iterator.hpp>

// Careful, don't call with lvalue expression that has side effects.
#define $items( c ) std::begin( *&c ), std::end( c )
