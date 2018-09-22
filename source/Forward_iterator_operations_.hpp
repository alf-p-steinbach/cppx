// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
#pragma once

#include <cppx/band-aid/core-language/size-types.hpp>       // cppx::(Size)
#include <cppx/band-aid/core-language/type-builders.hpp>    // cppx::(ref_)
#include <stdlib/iterator.hpp>                      // std::(begin, end, forward_iterator_tag)
#include <stdlib/c/stddef.hpp>                      // ptrdiff_t

namespace cppx
{
    using std::forward_iterator_tag;
    
    template< class Derived, class Value_type_param >
    class Forward_iterator_operations_
    {
        auto derived_self()
            -> ref_<Derived>
        { return static_cast<ref_<Derived>>( *this ); }

    public:
        // std::iterator_traits types:
        using difference_type       = Size;
        using value_type            = Value_type_param;  // decltype( *declval<Derived>() );
        using pointer               = ptr_<value_type>;
        using reference             = ref_<value_type>;
        using iterator_category     = forward_iterator_tag;

        using Value = Value_type_param;

        auto operator++()
            -> ref_<Derived>
        {
            derived_self().advance();
            return derived_self();
        }
        
        auto operator++( int )
            -> Derived
        {
            Derived original = derived_self();
            derived_self().advance();
            return original;
        }

        friend auto operator!=( ref_<const Derived> a, ref_<const Derived> b )
            -> bool
        { return not(a == b); }
    };

}  // namespace cppx
