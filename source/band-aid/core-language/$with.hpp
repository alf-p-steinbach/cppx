// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
#pragma once

// For example
// $with( Lock{ mutex } ) access_resource();

#if not defined( CPPX_NO_DOLLAR_NAMES )
#   define  $with   CPPX_WITH
#endif

#define CPPX_WITH( ... ) \
    if( const auto& _ = __VA_ARGS__; !!&_ )     // The !!&_ avoids warning about unused.
