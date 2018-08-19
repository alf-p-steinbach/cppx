#pragma once
#include <cppx/stdlib-wrappers/type-traits.hpp>     // cppx::is_base_and_derived
#include <stdlib/extension/type_builders.hpp>
#include <stdlib/utility.hpp>                       // std::enable_if_t

namespace cppx
{
    using namespace stdlib::ext::type_builders;

    template< class Derived, class Type,
        class = enable_if_t<is_base_and_derived<Type, Derived>>
        >
    inline auto downcasted_to_( ptr_<Type> p )
        -> ptr_<Derived>
    { return dynamic_cast<ptr_<Derived>>( p ); }

    template< class Derived, class Type,
        class = enable_if_t<is_base_and_derived<Type, Derived>>
        >
    inline auto downcasted_to_( ptr_<const Type> p )
        -> ptr_<const Derived>
    { return dynamic_cast<ptr_<const Derived>>( p ); }
}
