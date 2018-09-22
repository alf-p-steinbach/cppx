// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
#pragma once
#include <cppx/band-aid/standard-library/type-traits.hpp>   // cppx::is_base_and_derived
#include <cppx/band-aid/core-language/type-builders.hpp>    // cppx::(ptr_, ref_)
#include <stdlib/utility.hpp>                               // std::enable_if_t

namespace cppx
{
    namespace impl
    {
        template< class Derived, class Type >
        inline auto downcasted_to_( ptr_<Type> p )
            -> ptr_<Derived>
        {
            const auto pd = dynamic_cast<ptr_<Derived>>( p );
            return static_cast<ptr_<Type>>( pd ) == p? pd : nullptr;
        }
    }

    template<
        class Derived,
        class Type,
        class = enable_if_t<is_base_and_derived<Type, Derived>>
        >
    inline auto downcasted_to_( ptr_<Type> p )
        -> ptr_<Derived>
    { return impl::downcasted_to_<Derived>( p ); }

    template<
        class Derived,
        class Type,
        class = enable_if_t<is_base_and_derived<Type, Derived>>
        >
    inline auto downcasted_to_( ptr_<const Type> p )
        -> ptr_<const Derived>
    { return impl::downcasted_to_<const Derived>( p ); }
}
