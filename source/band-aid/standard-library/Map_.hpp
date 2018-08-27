// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
#pragma once
#include <cppx/type-builders.hpp>
#include <stdlib/unordered_map.hpp>             // std::unordered_map

namespace cppx{
    using std::unordered_map;

    template< class Key, class Value >
    class Map_
        : public unordered_map<Key, Value>
    {
    using Base = unordered_map<Key, Value>;
    public:
        using Base::unordered_map;
        using Base::operator[];

        auto operator[]( ref_<const Key> key ) const
            -> ref_<const Value>
        { return Base::at( key ); }
    };

    template< class Key, class Value, class Arg >
    auto is_in( ref_<const Map_<Key, Value>> map, ref_<const Arg> v )
        -> bool
    { return map.count( v ) > 0; }

}  // namespace cppx
