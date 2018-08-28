// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
#pragma once
#include <cppx/band-aid/standard-library/Exit_code.hpp>     // Included for convenience.
#include <cppx/diagnostics/Source_location.hpp>
#include <cppx/diagnostics/$source_location.hpp>
#include <stdlib/extension/hopefully_and_fail.hpp>

#define CPPX_FAIL( s ) \
    stdlib::ext::fail( CPPX_SOURCE_LOCATION().make_short_message( s ) )

#ifndef CPPX_NO_DOLLAR_NAMES
#   define  $fail   CPPX_FAIL
#endif

namespace cppx
{
    using stdlib::ext::hopefully;
    using stdlib::ext::fail;
}
