// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
#pragma once
//------------------------------------ String building

#include <cppx/text/is_char_type_.hpp>              // cppx::is_char_type_
#include <cppx/text/as_text_.hpp>                   // cppx::as_text_
#include <cppx/band-aid/core-language/type-builders.hpp>
#include <stdlib/string.hpp>                        // std::(basic_string)
#include <stdlib/utility.hpp>                       // std::enable_if_t

namespace cppx
{
    using std::enable_if_t;
    using std::basic_string;

    namespace impl
    {
        template< class Char, class = enable_if_t<is_char_type_<Char>> >
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
            { m_text += as_text_<Char>( v ); }
        };
    }  // namespace impl

    template< class Char, class = enable_if_t<is_char_type_<Char>> >
    class To_str_:
        public impl::To_str_<Char>
    {
    using Base = impl::To_str_<Char>;
    public:
        using Base::raw_str;
        using Base::str;
        using Base::append_text_for;

        operator ptr_<const Char>() const
        { return str().c_str(); }

        operator ref_<const basic_string<Char>>() const
        { return this->str(); }

        operator basic_string<Char>() &&
        { return move(*this).str(); }

        template< class Value >
        auto operator<<( ref_<const Value> v ) &
            -> ref_<To_str_>
        {
            append_text_for( v );
            return *this;
        }

        template< class Value >
        auto operator<<( ref_<const Value> v ) &&
            -> To_str_&&
        {
            append_text_for( v );
            return move( *this );
        }
    };

    template< class Char, class = enable_if_t<is_char_type_<Char>> >
    class To_stdstr_:
        public impl::To_str_<Char>
    {
    using Base = impl::To_str_<Char>;
    public:
        using Base::raw_str;
        using Base::str;
        using Base::append_text_for;

        operator ref_<const basic_string<Char>>() const
        { return str(); }

        operator basic_string<Char>() &&
        { return move(*this).str(); }

        template< class Value >
        auto operator<<( ref_<const Value> v ) &
            -> ref_<To_stdstr_>
        {
            append_text_for( v );
            return *this;
        }

        template< class Value >
        auto operator<<( ref_<const Value> v ) &&
            -> To_stdstr_&&
        {
            append_text_for( v );
            return move( *this );
        }
    };

    template< class Char, class = enable_if_t<is_char_type_<Char>> >
    class To_cstr_:
        public impl::To_str_<Char>
    {
    using Base = impl::To_str_<Char>;
    public:
        using Base::raw_str;
        using Base::str;
        using Base::append_text_for;

        operator ptr_<const Char>() const
        { return str().c_str(); }

        template< class Value >
        auto operator<<( ref_<const Value> v ) &
            -> ref_<To_cstr_>
        {
            append_text_for( v );
            return *this;
        }

        template< class Value >
        auto operator<<( ref_<const Value> v ) &&
            -> To_cstr_&&
        {
            append_text_for( v );
            return move( *this );
        }
    };

    using To_str        = To_str_<char>;
    using To_wstr       = To_str_<wchar_t>;
    using To_stdstr     = To_stdstr_<char>;
    using To_stdwstr    = To_stdstr_<wchar_t>;
    using To_cstr       = To_stdstr_<char>;
    using To_cwstr      = To_stdstr_<wchar_t>;

}  // namespace cppx
