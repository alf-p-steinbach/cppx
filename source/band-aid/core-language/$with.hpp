// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
#pragma once

// For example
// $with( Lock{ mutex } ) access_resource();

#define $with( ... ) \
    if( const auto& _ = __VA_ARGS__; !!&_ )     // The !!&_ avoids warning about unused.
