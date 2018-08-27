// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
#pragma once
#include <cppx/text/Lines_ref.hpp>

namespace cppx
{
    class Lines
    {
        string      m_text;

    public:
        using Iterator = Lines_ref::Iterator;

        operator Lines_ref() const
        { return Lines_ref( m_text ); }

        auto begin() const
            -> Iterator
        { return Iterator( m_text ); }

        auto end() const
            -> Iterator
        { return Iterator(); }

        Lines( string text ):
            m_text( move( text ) )
        {}
    };

}  // namespace cppx
