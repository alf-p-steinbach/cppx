// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
#pragma once
#include <cppx/band-aid/standard-library/type-traits.hpp>   // cppx::is_base_and_derived
#include <cppx/band-aid/core-language/type-builders.hpp>    // cppx::ref_
#include <stdlib/utility.hpp>                       // std::enable_if_t

namespace cppx
{
    using std::enable_if_t;

    // Whether a `static_cast<Derived*>( &o )` would do the Right Thing.
    // `true` if a downcast via `dynamic_cast` succeeds.
    // `false` if the `dynamic cast` fails or gives a sideways cast.
    template<
        class Derived, class Type,
        class = enable_if_t<is_base_and_derived<Type, Derived>>
        >
    inline auto is_really_a_( ref_<const Type> o )
        -> bool
    {
        const auto pd = dynamic_cast<ptr_<const Derived>>( &o );
        return static_cast<ptr_<const Type>>( pd ) == &o;
    }
}
