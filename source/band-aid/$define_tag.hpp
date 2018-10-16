#pragma once
#include <cppx/band-aid/core-language/type-builders.hpp>

#define $define_tag( name )                             \
    namespace tag                                       \
    {                                                   \
        using cppx::p_;                                 \
        using name = p_<struct name ## _tag>;           \
    }                                                   \
    static_assert( ::tag::name() == nullptr, "- support for semicolon - " )
