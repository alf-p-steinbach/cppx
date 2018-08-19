#pragma once
//------------------------------------ Generic access to std::to_string

#include <stdlib/extension/type_builders.hpp>   // ref_
#include <cppx/text/is_char_type_.hpp>  // cppx::is_char_type_
#include <stdlib/string.hpp>            // std::(basic_string, string, wstring, to_string, to_wstring)
#include <stdlib/utility.hpp>           // std::enable_if_t

namespace cppx
{
    using namespace stdlib::ext::type_builders;
    using std::enable_if_t;
    using std::basic_string;
    using std::string;
    using std::to_string;
    using std::to_wstring;
    using std::wstring;

    template< class Char, class = enable_if_t<is_char_type_<Char>> >
    struct Std_to_string_;

    template<>
    struct Std_to_string_<char>
    {
        template< class Value >
        auto operator()( ref_<const Value> v ) const
            -> string
        { 
            using std::to_string;
            return to_string( v );      // Support Koenig lookup (ADL), if any.
        }
    };

    template<>
    struct Std_to_string_<wchar_t>
    {
        template< class Value >
        auto operator()( ref_<const Value> v ) const
            -> wstring
        {
            using std::to_wstring;
            return to_wstring( v );     // Support Koenig lookup (ADL), if any.
        }
    };

    template< class Char, class Value, class = enable_if_t<is_char_type_<Char>> >
    auto to_string_( ref_<const Value> v )
        -> basic_string<Char>
    { return Std_to_string_<Char>{}( v ); }

}  // namespace cppx
