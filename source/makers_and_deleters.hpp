// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
#pragma once

#include <cppx/band-aid/core-language/type-builders.hpp>
#include <stdlib/memory.hpp>            // std::(default_delete)

namespace cppx{
    using std::default_delete;
    //using std::make_unique;
    //using std::make_shared;

    template< class Type >
    inline auto copy_of( rc_<Type> o )
        -> p_<Type>
    {
        return new Type( o );
    }

    template< class Item >
    inline void std_delete( pc_<Item> p )
    {
        default_delete<Item>()( const_cast<p_<Item>>( p ) );
    }

    template< class Item >
    inline void no_delete( pc_<Item> )
    {}

}  // namespace cppx
