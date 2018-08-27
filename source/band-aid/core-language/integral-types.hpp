// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
#pragma once
#include <stdlib/c/stddef.hpp>                  // byte
#include <stdlib/c/stdint.hpp>                  // intN_t, uintN_t; N in {8, 16, 32, 64}
#include <stdlib/extension/size_types.hpp>      // stdlib::ext::(Size, U_size)
#include <stdlib/type_traits.hpp>               // std::(is_signed_v, is_unsigned_v, is_same_v)

namespace cppx
{
    using std::is_signed_v;
    using std::is_unsigned_v;
    using std::is_same_v;

    inline namespace integral_types
    {
        using stdlib::ext::Size;            static_assert( is_signed_v<Size>, "!" );
        using stdlib::ext::U_size;          static_assert( is_unsigned_v<U_size>, "!" );
        using Unsigned_size = U_size;

        using Index = Size;             
        using U_index = U_size;         
        using Unsigned_index = U_index;
        static_assert( is_same_v<Index, stdlib::ext::Index>, "!" );
        static_assert( is_same_v<U_index, stdlib::ext::U_index>, "!" );

        using Byte = unsigned char; 
        using Signed_byte = signed char;
    }
}  // namespace cppx
