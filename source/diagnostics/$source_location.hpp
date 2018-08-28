// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
#pragma once
#include <cppx/diagnostics/Source_location.hpp>

#define $source_location \
    ::cppx::Source_location( __FILE__, __LINE__, 0, __func__ )
