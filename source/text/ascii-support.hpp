#pragma once
#include <cppx/core-language/integral-types.hpp>    // cppx::Byte
#include <cppx/text/is_char_type_.hpp>              // cppx::is_char_type_
#include <stdlib/extension/ascii.hpp>               // stdlib::ext::*
#include <stdlib/extension/type_builders.hpp>       // ref_, ptr_
#include <stdlib/c/string.hpp>                      // strlen
#include <stdlib/c/ctype.hpp>                       // isspace
#include <stdlib/string.hpp>                        // std::(string, wstring)
#include <stdlib/string_view.hpp>                   // std::string_view
#include <stdlib/type_traits.hpp>                   // std::make_unsigned
#include <stdlib/utility.hpp>                       // std::(enable_if_t)

namespace cppx
{
    using namespace stdlib::ext::type_builders;
    using std::basic_string;
    using std::basic_string_view;
    using std::enable_if_t;
    using std::make_unsigned_t;
    using std::string;
    using std::string_view;
    using std::wstring;

    namespace ascii = stdlib::ext::ascii;


    // Is-ASCII checking:

    template< class Integer >
    inline auto is_ascii( const Integer ch )
        -> bool
    { return ascii::contains( ch ); }

    template< class Char, class = enable_if_t<is_char_type_<Char>>>
    inline auto is_all_ascii( ref_<const basic_string_view<Char>> sv )
        -> bool
    { return ascii::contains_all( sv.begin(), sv.end() ); }

    template< class Char, class = enable_if_t<is_char_type_<Char>>>
    inline auto is_all_ascii( ptr_<const Char> s )
        -> bool
    { return is_all_ascii( basic_string_view<Char>( s ) ); }

    template< class Char, class = enable_if_t<is_char_type_<Char>>>
    inline auto is_all_ascii( ref_<const basic_string<Char>> s )
        -> bool
    { return is_all_ascii( basic_string_view<Char>( s ) ); }


    // wide_from_ascii

    template< class Char, class = enable_if_t<is_char_type_<Char>>>
    inline auto wide_from_ascii( ref_<const string_view> v )
        -> wstring
    { return wstring( v.begin(), v.end() ); }

    template< class Char, class = enable_if_t<is_char_type_<Char>>>
    inline auto wide_from_ascii( ptr_<const Char> s )
        -> wstring
    { return wide_from_ascii( basic_string_view<Char>( s ) ); }

    template< class Char, class = enable_if_t<is_char_type_<Char>>>
    inline auto wide_from_ascii( ref_<const basic_string<Char>> s )
        -> wstring
    { return wide_from_ascii( basic_string_view<Char>( s ) ); }


    //  Whitespace checking

    // Depends on the C level locale (setlocale)
    template< class Char, class = enable_if_t<is_char_type_<Char>>>
    inline auto is_cstdlib_space( const Char ch ) -> bool;

    template<>
    inline auto is_cstdlib_space<char>( const char ch )
        -> bool
    { return !!::isspace( static_cast<Byte>( ch ) ); }

    template<>
    inline auto is_cstdlib_space<wchar_t>( const wchar_t ch )
        -> bool
    { return !!::iswspace( ch ); }

    // Is independent of locale
    template< class Char, class = enable_if_t<is_char_type_<Char>>>
    inline auto is_ascii_whitespace( const Char ch )
        -> bool
    { return is_ascii( ch ) and is_cstdlib_space( ch ); }

    template< class Char, class = enable_if_t<is_char_type_<Char>>>
    inline auto is_all_ascii_whitespace( ref_<const basic_string_view<Char>> sv )
        -> bool
    {
        for( const Char ch : sv )
        {
            if( not is_ascii_whitespace( ch ) )
            {
                return false;
            }
        }
        return true;
    }

}  // namespace cppx
