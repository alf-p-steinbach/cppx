#pragma once

#include <type_traits>          // std::remove_reference_t

namespace cppx{
    using std::remove_reference_t;

    namespace impl{
        template< class Other, class Type >
        struct With_const_as_t_
        {
            using T = Type;
        };

        template< class Other, class Type >
        struct With_const_as_t_<const Other, Type>
        {
            using T = const Type;
        };
    }  // namespace impl

    // The enumeration type allows templating a type on constness without introducing
    // an open ended number of possible instantiations, but just the two, m and c.
    struct Constness{ enum Enum { m, c }; };        // m = mutable, c = const

    template< Constness::Enum c > struct As_type_;

    template<>
    struct As_type_<Constness::m>
    {
        using T = void;
    };

    template<>
    struct As_type_<Constness::c>
    {
        using T = const void;
    };

    template< class Other, class Type >
    using const_like_ = typename impl::With_const_as_t_<
        remove_reference_t<Other>, Type
        >::T;

    template< Constness::Enum c, class Type >
    using with_constness_ = const_like_<typename As_type_<c>::T, Type>;

}  // namespace cppx
