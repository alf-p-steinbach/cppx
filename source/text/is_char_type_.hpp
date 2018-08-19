#pragma once
#include <stdlib/type_traits.hpp>   // std::is_same_v

namespace cppx
{
    using std::is_same_v;

    template< class Char >
    constexpr bool is_char_type_ = (is_same_v<Char, char> or is_same_v<Char, wchar_t>);

}  // namespace cppx
