﻿// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
#pragma once
#include <cppx/band-aid/core-language/size_types.hpp>
#include <stdlib/c/stddef.hpp>                  // byte
#include <stdlib/c/stdint.hpp>                  // intN_t, uintN_t; N in {8, 16, 32, 64}

namespace cppx
{
    inline namespace integral_types
    {
        using cppx::size_types::Size;
        using cppx::size_types::Index;
        using cppx::size_types::Unsigned_size;
        using cppx::size_types::Unsigned_index;

        using Byte          = unsigned char; 
        using Signed_byte   = signed char;
    }
}  // namespace cppx
