#pragma once
#include <stdlib/extension/type_builders.hpp>

#include <stdlib/c/string.hpp>      // strlen
#include <stdlib/string.hpp>        // std::(wstring)
#include <stdlib/utility.hpp>       // std::(enable_if_t, move)
#include <stdlib/type_traits.hpp>   // std::is_same

namespace cppx {
    using namespace stdlib::ext::type_builders;
    using std::basic_string;
    using std::enable_if_t;
    using std::is_same_v;
    using std::move;
    using std::string;
    using std::wstring;


    //------------------------------------ Type classification

    template< class Char >
    constexpr bool is_char_type = (is_same_v<Char, char> or is_same_v<Char, wchar_t>);

    inline auto is_ascii( const char ch )
        -> bool
    {
        using Byte = unsigned char;
        return Byte( ch ) < 128;
    }


    //------------------------------------ Misc

    inline auto wide_from_ascii( raw_array_<const char> s )
        -> wstring
    { return wstring( s, s + strlen( s ) ); }



    //------------------------------------ Generic access to std::to_string

    template< class Char > struct Std_to_string_;

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

    template< class Char, class Value >
    auto to_string_( ref_<const Value> v )
        -> basic_string<Char>
    { return Std_to_string_<Char>{}( v ); }


    //------------------------------------ Reasonably efficient as_text

    template< class Char, class Value >
    inline auto as_text_( ref_<const Value> v )
        -> basic_string<Char>
    { return to_string_<Char>( v ); }

    template< class Char >
    auto as_text_( ref_<const basic_string<Char>> s )
        -> ref_<const basic_string<Char>>
    { return s; }

    template< class Char, class = enable_if_t< is_char_type<Char> > >
    auto as_text_( const ptr_<const Char> s )
        -> ptr_<const Char>
    { return s; }

    template< class Char, class = enable_if_t< is_char_type<Char> > >
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


    //------------------------------------ String building

    template< class Char >
    class To_str_
    {
        basic_string<Char>  m_text;

    public:
        auto raw_str() const
            -> ptr_<const Char>
        { return m_text.c_str(); }

        auto str() const&
            -> ref_<const basic_string<Char>>
        { return m_text; }

        auto str() &&
            -> basic_string<Char>
        { return move( m_text ); }

        template< class Value >
        void append_text_for( ref_<const Value> v )
        {
            m_text += as_text_<Char>( v );
        }

        operator ptr_<const Char>() const
        {
            return m_text.c_str();
        }

        operator ref_<const basic_string<Char>>() const
        {
            return m_text;
        }

        operator basic_string<Char>() &&
        {
            return move( m_text );
        }

        template< class Value >
        auto operator<<( ref_<const Value> v )
            -> ref_<To_str_>
        {
            append_text_for( v );
            return *this;
        }
    };

    using To_str = To_str_<char>;
    using To_wstr = To_str_<wchar_t>;

}  // namespace cppx
