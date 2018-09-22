// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
#pragma once
#include <stdlib/extension/size_types.hpp>      // stdlib::ext::(Size, U_size)

namespace cppx
{
    inline namespace size_types
    {
        using Size                  = stdlib::ext::Size;
        using Index                 = Size;
        using Unsigned_size         = stdlib::ext::U_size;
        using Unsigned_index        = Unsigned_size;
    }
}  // namespace cppx

#if 0 or defined( CPPX_SIZE_TYPE_CHECKS )
#   include <stdlib/type_traits.hpp>            // std::(is_signed_v, is_unsigned_v, is_same_v)
    namespace cppx{
        static_assert( std::is_signed_v<Size>, "!" );
        static_assert( std::is_unsigned_v<Unsigned_size>, "!" );
        static_assert( std::is_same_v<Index, stdlib::ext::Index>, "!" );
        static_assert( std::is_same_v<Unsigned_index, stdlib::ext::U_index>, "!" );
    }
#endif
