#pragma once
#include <stdlib/c/stdint.hpp>              // intN_t, uintN_t; for N in {8, 16, 32, 64}
#include <stdlib/extension/size_types.hpp>  //  Size, Index, U_size, U_index

namespace cppx
{
    using stdlib::ext::Size;
    using stdlib::ext::Index;
    using stdlib::ext::U_size;
    using stdlib::ext::U_index;
    using Byte = unsigned char; 
    using Signed_byte = signed char;
}  // namespace cppx
