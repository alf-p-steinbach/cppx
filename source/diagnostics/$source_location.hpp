// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
#pragma once
#include <cppx/diagnostics/Source_location.hpp>

#define CPPX_SOURCE_LOCATION() \
    ::cppx::Source_location{ __FILE__, __LINE__, {}, __func__ }

#ifndef CPPX_NO_DOLLAR_NAMES
#   define  $source_location    CPPX_SOURCE_LOCATION
#endif
