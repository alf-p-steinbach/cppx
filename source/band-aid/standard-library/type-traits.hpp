#pragma once
#include <stdlib/type_traits.hpp>       // std::is_base_of

namespace cppx
{
    template< class Base, class Derived >
    constexpr bool is_base_and_derived = std::is_base_of_v<Base, Derived>;

    template< class T, class U >
    constexpr bool is_same_type = std::is_same_v<T, U>;

    template< class T, class U >
    constexpr bool is_a = is_base_and_derived<T, U> or is_same_type<T, U>;
}
