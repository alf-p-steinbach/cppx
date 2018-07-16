#pragma once
#include <stdlib/extension/type_builders.hpp>       // stdlib::ext::(ref_)
#include <stdlib/iterator.hpp>                      // std::(begin, end, forward_iterator_tag)
#include <stdlib/c/stddef.hpp>                      // ptrdiff_t

namespace cppx{
    using namespace stdlib::ext::type_builders;     // ptr_, ref_

    using std::forward_iterator_tag;
    
    using Size = ptrdiff_t;

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
