// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
#pragma once
//------------------------------------ Reasonably efficient `as_text_()`

#include <cppx/text/is_char_type_.hpp>              // cppx::is_char_type_
#include <cppx/text/to_string_.hpp>                 // cppx::to_string_
#include <cppx/band-aid/core-language/type-builders.hpp>
#include <stdlib/string.hpp>                        // std::(basic_string)
#include <stdlib/utility.hpp>                       // std::enable_if_t

namespace cppx
{
    using std::basic_string;
    using std::enable_if_t;

    template< class Char, class Value, class = enable_if_t<is_char_type_<Char>> >
    inline auto as_text_( ref_<const Value> v )
        -> basic_string<Char>
    { return to_string_<Char>( v ); }

    template< class Char >
    auto as_text_( ref_<const basic_string<Char>> s )
        -> ref_<const basic_string<Char>>
    { return s; }

    template< class Char, class = enable_if_t< is_char_type_<Char> > >
    auto as_text_( const ptr_<const Char> s )
        -> ptr_<const Char>
    { return s; }

    template< class Char, class = enable_if_t< is_char_type_<Char> > >
    auto as_text_( const ptr_<Char> s )
        -> ptr_<const Char>
    { return s; }

    template< class Char >
    auto as_text_( const bool v )
        -> ptr_<const Char>
    { return (v? "true" : "false"); }

    template< class Char >
    auto as_text_( const Char v )
        -> string
    { return string{ v }; }

}  // namespace cppx
