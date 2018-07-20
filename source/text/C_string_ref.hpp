#pragma once
#include <stdlib/extension/type_builders.hpp>
#include <stdlib/extension/size_types.hpp>
#include <stdlib/algorithm.hpp>     // std::min
#include <stdlib/string.hpp>        // std::basic_string

namespace cppx {
    using namespace stdlib::ext::type_builders;     // ptr_
    using std::basic_string;
    using std::char_traits;
    using std::min;
    using stdlib::ext::Size;

    template< class Char >
    class C_string_ref
    {
    private:
        ptr_<const Char>    m_s;
        mutable Size        m_length    = -1;

    public:
        auto s() const -> ptr_<const Char> { return m_s; }

        operator ptr_<const Char>() const { return s(); }

        auto length() const
            -> Size
        { return (m_length == -1? m_length = char_traits<Char>::length( m_s ) : m_length); }

        auto std_string() const
            -> basic_string<Char>
        { return basic_string<Char>( s(), length() ); }

        operator basic_string<Char>() const { return std_string(); }

        friend auto compare( ref_<const C_string_ref> a, ref_<const C_string_ref> b )
            -> int
        {
            const int length_of_a       = a.length();
            const int length_of_b       = b.length();
            const int common_length     = min( length_of_a, length_of_b );
            return char_traits<Char>::compare( a, b, common_length + 1 );
        }

        auto begin() const  -> ptr_<const Char>     { return m_s; }
        auto end() const    -> ptr_<const Char>     { return m_s + length(); }

        C_string_ref( const ptr_<const Char> s )
            : m_s{ s }
        {}

        C_string_ref( ref_<const std::basic_string<Char>> s )
            : m_s{ s.c_str() }
        {}
    };

    using C_widestring_ref = C_string_ref<wchar_t>;
    using C_bytestring_ref = C_string_ref<char>;
}  // namespace cppx