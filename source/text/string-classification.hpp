// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
#pragma once
#include <cppx/text/ascii-support.hpp>          // cppx::*
#include <cppx/type-builders.hpp>
#include <stdlib/string.hpp>                    // std::(wstring)
#include <stdlib/string_view.hpp>               // std::string_view

namespace cppx
{
    using std::basic_string;
    using std::basic_string_view;

    // is_empty

    template< class Char >
    inline auto is_empty( ptr_<const Char> s )
        -> bool
    { return s[0] == Char( 0 ); }

    template< class Char >
    inline auto is_empty( ref_<const basic_string_view<Char>> v )
        -> bool
    { return s.empty(); }

    template< class Char >
    inline auto is_empty( ref_<const basic_string<Char>> s )
        -> bool
    { return s.empty(); }

    //  is_whitespace

    template< class Char, class = enable_if_t<is_char_type_<Char>> >
    inline auto is_whitespace( const Char ch ) -> bool;

    template<>
    inline auto is_whitespace<char>( const char ch )
        -> bool
    { return is_ascii_whitespace( ch ); }

    template<>
    inline auto is_whitespace<wchar_t>( const wchar_t ch )
        -> bool
    { return is_cstdlib_space( ch ); }

    //  is_all_whitespace

    template< class Char >
    inline auto is_all_whitespace( ref_<const basic_string_view<Char>> sv ) -> bool;

    template<>
    inline auto is_all_whitespace<char>( ref_<const basic_string_view<char>> sv )
        -> bool
        = delete;           // TODO: UTF-8

    template<>
    inline auto is_all_whitespace<wchar_t>( ref_<const basic_string_view<wchar_t>> sv )
        -> bool
    {
        for( wchar_t const ch : sv )
        {
            if( not is_whitespace( ch ) )
            {
                return false;
            }
        }
        return true;
    }

    template< class Char >
    inline auto is_all_whitespace( ptr_<const Char> s )
        -> bool
    { return is_all_whitespace( string_view( s ) ); }

    template< class Char >
    inline auto is_all_whitespace( ref_<const basic_string<Char>> s )
        -> bool
    { return is_all_whitespace( string_view( s ) ); }

}  // namespace cppx
