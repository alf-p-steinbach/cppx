// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
#pragma once
#include <cppx/band-aid/standard-library/Exit_code.hpp>     // Included for convenience.
#include <cppx/diagnostics/Source_location.hpp>
#include <cppx/diagnostics/$source_location.hpp>
#include <stdlib/extension/hopefully_and_fail.hpp>

#define $fail( s ) \
    stdlib::ext::fail( $source_location.make_short_message( s ) )

namespace cppx
{
    using stdlib::ext::hopefully;
    using stdlib::ext::fail;
}
