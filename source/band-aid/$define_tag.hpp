#pragma once
#include <stdlib/extension/type_builders.hpp>

#define CPPX_DEFINE_TAG( name )                         \
    namespace tag                                       \
    {                                                   \
        using stdlib::ext::ptr_;                        \
        using name = ptr_<struct name ## _tag>;         \
    }                                                   \
    static_assert( ::tag::name() == nullptr, "- support for semicolon - " )

#ifndef CPPX_NO_DOLLAR_NAMES
#   define  $define_tag     CPPX_DEFINE_TAG
#endif
