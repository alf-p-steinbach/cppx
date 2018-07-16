#pragma once
#include <cppx/diagnostics/Source_location.hpp>
#include <stdlib/extension/hopefully_and_fail.hpp>

#ifndef CPPX_NO_DOLLAR_NAMES
#   define  $fail   CPPX_FAIL
#endif

#define CPPX_FAIL( s ) \
    stdlib::ext::fail( CPPX_SOURCE_LOCATION().message( s ) )
