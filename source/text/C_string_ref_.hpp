// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
#pragma once
#include <cppx/band-aid/core-language/type-builders.hpp>
#include <stdlib/extension/size_types.hpp>
#include <stdlib/algorithm.hpp>     // std::min
#include <stdlib/string.hpp>        // std::basic_string

namespace cppx {
    using std::basic_string;
    using std::char_traits;
    using std::min;
    using stdlib::ext::Size;

    template< class Char >
    class C_string_ref_
    {
    private:
        ptr_<const Char>    m_s;
        mutable Size        m_length    = -1;

    public:
        auto ptr() const
            -> ptr_<const Char>
        { return m_s; }

        auto str() const
            -> basic_string<Char>
        { return basic_string<Char>( ptr(), length() ); }

        operator ptr_<const Char>()  const { return ptr(); }

        auto length() const
            -> Size
        { return (m_length == -1? m_length = char_traits<Char>::length( m_s ) : m_length); }

        friend auto compare( ref_<const C_string_ref_> a, ref_<const C_string_ref_> b )
            -> int
        {
            const int length_of_a       = a.length();
            const int length_of_b       = b.length();
            const int common_length     = min( length_of_a, length_of_b );
            return char_traits<Char>::compare( a, b, common_length + 1 );
        }

        auto begin() const  -> ptr_<const Char>     { return m_s; }
        auto end() const    -> ptr_<const Char>     { return m_s + length(); }

        C_string_ref_( const ptr_<const Char> s )
            : m_s( s )
        {}

        C_string_ref_( ref_<const std::basic_string<Char>> s )
            : m_s( s.c_str() )
            , m_length( s.length() )
        {}
    };

    using C_string_ref      = C_string_ref_<char>;
    using C_wstring_ref     = C_string_ref_<wchar_t>;
}  // namespace cppx
