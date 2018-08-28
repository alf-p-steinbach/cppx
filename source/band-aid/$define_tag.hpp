#pragma once
#include <stdlib/extension/type_builders.hpp>

#define $define_tag( name )                             \
    namespace tag                                       \
    {                                                   \
        using stdlib::ext::ptr_;                        \
        using name = ptr_<struct name ## _tag>;         \
    }                                                   \
    static_assert( ::tag::name() == nullptr, "- support for semicolon - " )
