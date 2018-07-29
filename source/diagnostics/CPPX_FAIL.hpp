#pragma once
#include <cppx/diagnostics/Source_location.hpp>
#include <cppx/process/exit-codes.hpp>              // Included for convenience.
#include <stdlib/extension/hopefully_and_fail.hpp>

#define CPPX_FAIL( s ) \
    stdlib::ext::fail( CPPX_SOURCE_LOCATION().make_short_message( s ) )

#ifndef CPPX_NO_DOLLAR_NAMES
#   define  $fail   CPPX_FAIL
#endif
