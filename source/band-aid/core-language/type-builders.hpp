// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
#pragma once

#include <stdlib/extension/type_builders.hpp>

namespace cppx
{
    inline namespace type_builders
    {
        using namespace stdlib::ext::type_builders;

        // using impl::type_;

        // using impl::ref_;
        // using impl::unref_;
        // using impl::ptr_;
        // using impl::unptr_;
        // using impl::signed_;
        // using impl::unsigned_;
        // using impl::const_;
        // using impl::unconst_;

        // using impl::temp_ref_;
        // using impl::forwarding_ref_;
        // using impl::array_of_;
        // using impl::raw_array_;
        // using impl::raw_array_of_;
        // using impl::item_type_of_;

        template< class Type >  using c_    = const_<Type>;
        template< class Type >  using p_    = ptr_<Type>;
        template< class Type >  using pc_   = p_<c_<Type>>;
        template< class Type >  using r_    = ref_<Type>;
        template< class Type >  using rc_   = r_<c_<Type>>;
    }
}
