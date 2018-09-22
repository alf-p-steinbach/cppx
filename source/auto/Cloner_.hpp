// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
#pragma once

// Non-intrusive cloning using the original established type (type erasure).
// This is intended as a minimal “black box” class with no conveniences.

#include <cppx/band-aid/core-language/$with.hpp>
#include <cppx/band-aid/core-language/type-builders.hpp>
#include <cppx/band-aid/standard-library/type-traits.hpp>   // cpppx::is_base_and_derived
#include <cppx/makers_and_deleters.hpp>                     // cppx::(copy_of, std_delete)
#include <cppx/class-kind/No_copy.hpp>                      // cppx::No_copy
#include <cppx/auto/Scope_guard_.hpp>
#include <stdlib/functional.hpp>        // std::(function)
#include <stdlib/memory.hpp>            // std::(unique_ptr
#include <utility>                      // std::(enable_if_t, move)

namespace cppx{
    using std::enable_if_t;
    using std::function;
    using std::move;
    using std::unique_ptr;

    template< class Item >
    class Cloner_
        : public No_copy
    {
        using Clone_func    = auto( pc_<Item> ) -> p_<Item>;
        using Delete_func   = void( pc_<Item> );

        struct Instantiation_funcs
        {
            p_<Clone_func>          clone_func;
            p_<Delete_func>         delete_func;
        };

        using Instantiation_func = auto() -> Instantiation_funcs;

        p_<Item>                    m_p_item;
        p_<Instantiation_func>      m_instantiation;

        Cloner_(
            c_<p_<Item>>                    p_item,
            c_<p_<Instantiation_func>>      instantiation
            ) noexcept :
            m_p_item( p_item ),
            m_instantiation( instantiation )
        {}

    public:
        auto p() const -> p_<Item> { return m_p_item; }

        auto clone() const
            -> Cloner_
        {
            if( not m_p_item )
            {
                return Cloner_();
            }
            return Cloner_( m_instantiation().clone_func( m_p_item ), m_instantiation );
        }

        friend void swap( r_<Cloner_> a, r_<Cloner_> b )
            noexcept
        {
            using std::swap;
            swap(   a.m_p_item,         b.m_p_item      );
            swap(   a.m_instantiation,  b.m_instantiation );
        }

        auto operator=( Cloner_&& other )
            -> r_<Cloner_>
        {
            swap( *this, other );
            return *this;
        }

        Cloner_() noexcept :
            m_p_item(),
            m_instantiation()
        {}

        Cloner_( Cloner_&& other ) noexcept :
            Cloner_()
        {
            swap( *this, other );
        }

        template<
            class Derived,
            class = enable_if_t<is_base_and_derived<Item, Derived>>
            >
        Cloner_( c_<p_<Derived>> p_arg ) noexcept :
            m_p_item        ( p_arg ),
            m_instantiation ( []() -> Instantiation_funcs
                {
                    return
                    {
                        []( pc_<Item> p ) -> p_<Item>
                        {
                            return copy_of( *static_cast<p_<const Derived>>( p ) );
                        },
                        []( pc_<Item> p ) -> void
                        {
                            std_delete( static_cast<pc_<Derived>>( p ) );
                        }
                    };
                } )
        {}

        template<
            class Derived,
            class = enable_if_t<is_base_and_derived<Item, Derived>>
            >
        Cloner_( unique_ptr<Derived> p ) noexcept :
            Cloner_( p_.release() )
        {}

        ~Cloner_()
        {
            if( m_p_item ){ m_instantiation().delete_func( m_p_item ); }
        }
    };

}  // namespace cppx
