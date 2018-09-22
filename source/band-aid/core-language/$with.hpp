// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
#pragma once

#include <cppx/band-aid/core-language/type-builders.hpp>

// For example
// $with( Lock( mutex ) ) access_resource();
// $with_const( Lock( mutex ) ) access_resource();
// $with( cppx::const_<Lock>( mutex ) ) access_resource();

#define $with( ... ) \
    if( auto&& _ = __VA_ARGS__; !!&_ )      // The !!&_ avoids warning about unused.

#define $with_const( ... ) \
    if( const auto& _ = __VA_ARGS__; !!&_ )
