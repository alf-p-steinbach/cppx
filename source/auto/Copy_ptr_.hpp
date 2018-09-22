// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
#pragma once
// TODO:
//
// Copying a Copy_ptr_ copies the Derived object, using the type established
// at original pointer construction.

#include <cppx/band-aid/core-language/$with.hpp>
#include <cppx/band-aid/core-language/type-builders.hpp>
#include <cppx/band-aid/standard-library/type-traits.hpp>   // cpppx::is_base_and_derived

#include <cppx/auto/Cloner_.hpp>

namespace cppx{
    using std::default_delete;

    template< class Item >
    class Copy_ptr_
    {
        Cloner_<Item>   m_cloner;

    public:
        using Self = Copy_ptr_;

        explicit operator bool() const          { return !!m_cloner.p(); }
        auto operator*() const -> r_<Item>      { return *m_cloner.p(); }
        auto operator->() const -> p_<Item>     { return m_cloner.p(); }

        friend void swap( r_<Copy_ptr_> a, r_<Copy_ptr_> b )
            noexcept
        {
            using std::swap;
            swap( a.m_cloner, b.m_cloner );
        }

        auto operator=( Copy_ptr_ other )
            -> r_<Copy_ptr_>
        {
            swap( other, *this );
            return *this;
        }

        Copy_ptr_() {}

        Copy_ptr_( rc_<Copy_ptr_> other ): m_cloner( other.m_cloner.clone() ) {}

        template<
            class Derived,
            class = enable_if_t<is_base_and_derived<Item, Derived>>
            >
        Copy_ptr_( unique_ptr<Derived> p ): m_cloner( move( p ) ) {}

        template<
            class Derived,
            class = enable_if_t<is_base_and_derived<Item, Derived>>
            >
        Copy_ptr_( c_<p_<Derived>> p ): Self( unique_ptr<Derived>( p ) ) {}

        //template<
        //    class Derived,
        //    class = enable_if_t<is_base_and_derived<Item, Derived>>
        //    >
        //Copy_ptr_( c_<p_<Derived>> p, Deleter d )
        //{
        //    auto&& cleanup = make_scope_guard( [&]{ d( p ); } );
        //    m_p_item        = p;
        //    m_delete_func   = ([p, d]{ d( p ); });
        //    m_copy_func     = &copy_via_new<Derived>;
        //    cleanup.dismiss();
        //}

        ~Copy_ptr_() {}
    };

}  // namespace cppx
