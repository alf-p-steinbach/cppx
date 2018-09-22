// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
#pragma once
#include <cppx/band-aid/core-language/integral-types.hpp>
#include <cppx/band-aid/$define_tag.hpp>
#include <cppx/band-aid/Range_.hpp>                 // cppx::Range
#include <cppx/band-aid/core-language/type-builders.hpp>    // cppx::(ref_, raw_array_of_)
#include <stdlib/algorithm.hpp>                     // std::(find, binary_search)
#include <stdlib/initializer_list.hpp>              // std::initializer_list
#include <stdlib/iterator.hpp>                      // std::(begin, end, iterator_traits)
#include <stdlib/utility.hpp>                       // std::move
#include <stdlib/unordered_set.hpp>                 // std::unordered_set

$define_tag( Iterators );       // tag::Iterators
$define_tag( Values );          // tag.:Values

namespace cppx{
    using std::begin;
    using std::binary_search;
    using std::end;
    using std::find;
    using std::initializer_list;
    using std::iterator_traits;
    using std::move;
    using std::unordered_set;
    using stdlib::ext::Size;

    struct Set
    {
        struct Relationship
        {
            enum Enum
            {
                within, equals, covers, intersects, separate_from
            };

            constexpr static auto reversed( const Enum rel )
                -> Enum
            {
                switch( rel )
                {
                    case within:            return covers;
                    case equals:            return equals;
                    case covers:            return within;
                    case intersects:        return intersects;
                    case separate_from:     return separate_from;
                }
            }
        };
    };

    template< class Key >
    class Set_
        : public unordered_set<Key>
    {
    public:
        Set_() {}

        Set_( ref_<const Key> a_key )
            : unordered_set<Key>{ &a_key, &a_key + 1 }
        {}

        // Only meaningful for integer-like Key:
        template< class Integer >
        Set_( ref_<const Range_<Integer>> range )
            : unordered_set<Key>{ range.begin(), range.end() }
        {}
        
        Set_( tag::Values, initializer_list<Key> values )
            : unordered_set<Key>{ move( values ) }
        {}
        
        template< class Input_iterator >
        Set_( tag::Iterators, const Input_iterator first, const Input_iterator beyond )
            : unordered_set<Key>{ first, beyond }
        {}
    };

#ifdef CPPX_USE_DEDUCTION_GUIDES
    // Template parameter deduction guides:
    template< class Integer >
    Set_( ref_<const Range_<Integer>> )
        -> Set_<Integer>;

    template< class Key >
    Set_( initializer_list<Key> )
        -> Set_<Key>;
    
    template< class Input_iterator >
    Set_( tag::Iterators, Input_iterator, Input_iterator )
        -> Set_<typename iterator_traits<Input_iterator>::value_type>;
#endif

    // Explicit conversions for e.g. deduction-challenged compiler:
    template< class Key >
    inline auto as_set( ref_<const Key> a_key )
        -> Set_<Key>
    { return { a_key }; }
    
    template< class Integer >
    inline auto as_set( ref_<const Range_<Integer>> range )
        -> Set_<Integer>
    { return { range }; }
    
    template< class Key >
    inline auto as_set( initializer_list<Key> values )
        -> Set_<Key>
    { return { values }; }

    template< class Input_iterator >
    inline auto as_set(
        const tag::Iterators    iterators_tag,
        const Input_iterator    first,
        const Input_iterator    beyond
        )
        -> Set_<typename iterator_traits<Input_iterator>::value_type>
    {
        using Value = typename iterator_traits<Input_iterator>::value_type;
        return { iterators_tag, first, beyond };
    }

        // Basic set union
    template< class Key >
    auto operator+( ref_<const Set_<Key>> a, ref_<const Set_<Key>> b )
        -> Set_<Key>
    {
        ref_<const Set_<Key>> smallest  = (a.size() < b.size()? a : b);
        ref_<const Set_<Key>> largest   = (a.size() < b.size()? b : a);
        
        Set_<Key> result{ largest };
        for( ref_<const Key> key : smallest )
        {
            result.insert( key );
        }
        return result;
    }

    template< class Key, class Arg >
    auto operator+( ref_<const Set_<Key>> a, ref_<const Arg> b )
        -> Set_<Key>
    { return a + Set_<Key>{ b }; }
    
    template< class Key, class Arg >
    auto operator+(  ref_<const Arg> a, ref_<const Set_<Key>> b )
        -> Set_<Key>
    { return Set_<Key>{ a } + b; }

    // Basic set difference
    template< class Key >
    auto operator-( ref_<const Set_<Key>> a, ref_<const Set_<Key>> b )
        -> Set_<Key>
    {
        Set_<Key> result{ a };
        for( ref_<const Key> key : b )
        {
            result.erase( key );
        }
        return result;
    }

    template< class Key, class Arg >
    auto operator-( ref_<const Set_<Key>> a, ref_<const Arg> b )
        -> Set_<Key>
    { return a - Set_<Key>{ b }; }
    
    // Efficiency for temporaries
    template< class Key >
    auto operator-( Set_<Key>&& a, ref_<const Set_<Key>> b )
        -> Set_<Key>&&
    {
        for( ref_<const Key> key : b )
        {
            a.erase( key );
        }
        return move( a );
    }

    // Membership check
    template< class Key, class Arg >
    auto is_in( ref_<const Set_<Key>> set, ref_<const Arg> v )
        -> bool
    { return set.count( v ) > 0; }

    // General relationship check
    // ...

    
    //----------------------------------------- Related utility functions:
    
    template< class It, class Arg >
    auto is_in_range( const It begin, const It end, ref_<const Arg> v )
        -> bool
    { return find( begin, end, v ) != end; }

    template< class Key, Size n, class Arg >
    auto is_in( ref_<raw_array_of_<n, const Key>> a, ref_<const Arg> v )
        -> bool
    { return is_in_range( begin( a ), end( a ), v ); }

    template< class It, class Arg >
    auto is_in_sorted_range( const It begin, const It end, ref_<const Arg> v )
        -> bool
    { return binary_search( begin, end, v ); }

    template< class Key, Size n, class Arg >
    auto is_in_sorted( ref_<raw_array_of_<n, const Key>> a, ref_<const Arg> v )
        -> bool
    { return is_in_sorted_range( begin( a ), end( a ), v ); }

}  // namespace cppx
