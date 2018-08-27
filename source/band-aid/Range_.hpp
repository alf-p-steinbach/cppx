// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
#pragma once
#include <cppx/Forward_iterator_operations_.hpp>

namespace cppx{
    
    template< class Integer >
    class Range_
    {
        Integer     m_first;
        Integer     m_beyond;

        class Iterator:
            public Forward_iterator_operations_<Iterator, Integer>
        {
            Integer     m_current;

        public:
            void advance() { ++m_current; }

            auto operator*() const
                -> Integer
            { return m_current; }
            
            friend auto operator==( ref_<const Iterator> a, ref_<const Iterator> b )
                -> bool
            { return a.m_current == b.m_current; }

            explicit Iterator( const Integer value )
                : m_current{ value }
            {}
        };

    public:
        auto begin() const  -> Iterator     { return Iterator{ m_first }; }
        auto end() const    -> Iterator     { return Iterator{ m_beyond }; }

        Range_( const Integer first, const Integer last )
            : m_first{ first }
            , m_beyond{ static_cast<Integer>( last + 1 ) }
        {}
    };

}  // namespace cppx
