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
    inline auto is_really_a_( ref_<const Type> o )
        -> bool
    { return !!dynamic_cast<ptr_<const Derived>>( &o ); }
}
