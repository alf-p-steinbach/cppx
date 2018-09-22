// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
#pragma once
#include <cppx/band-aid/standard-library/Exit_code.hpp>     // Included for convenience.
#include <cppx/exceptions/hopefully_and_fail.hpp>
#include <cppx/diagnostics/$source_location.hpp>

#define $fail( s ) \
    cppx::fail( $source_location.make_short_message( s ) )
