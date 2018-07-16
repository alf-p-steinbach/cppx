#pragma once
#include <stdlib/extension/hopefully_and_fail.hpp>
#include <stdlib/extension/type_builders.hpp>
#include <stdlib/unordered_map.hpp>             // std::unordered_map

namespace cppx{
    using std::unordered_map;
    using namespace stdlib::ext::hopefully_and_fail;
    using namespace stdlib::ext::type_builders;

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
    auto in( ref_<const Map_<Key, Value>> map, ref_<const Arg> v )
        -> bool
    { return map.count( v ) > 0; }

}  // namespace cppx
