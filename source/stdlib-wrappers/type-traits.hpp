#pragma once
#include <type_traits>          // std::is_base_of

namespace cppx
{
    using std::is_base_of;

    // is_base_and_derived<B, D> == std::is_base_of_v<B, D>
    template< class Base, class Derived >
    constexpr bool is_base_and_derived = is_base_of<Base, Derived>::value;
}
