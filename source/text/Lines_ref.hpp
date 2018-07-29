#pragma once
#include <cppx/Forward_iterator_operations_.hpp>    // cppx::Forward_iterator_operations_
#include <cppx/stdlib-wrappers/String_view.hpp>     // cppx::String_view
#include <stdlib/extension/size_types.hpp>          // stdlib::ext::Size
#include <stdlib/extension/type_builders.hpp>       // stdlib::(ref_, *)
#include <stdlib/string_view.hpp>                   // std::string_view
#include <stdlib/string.hpp>                        // std::string

namespace cppx
{
    using namespace stdlib::ext::type_builders;
    using cppx::Forward_iterator_operations_;
    using cppx::String_view;
    using std::string;
    using stdlib::ext::Size;

    class Lines_ref
    {
        String_view     m_view;

    public:
        class Iterator
            : public Forward_iterator_operations_<Iterator, String_view>
        {
            ptr_<const char>    m_p_beyond_all;
            String_view         m_current;              // Includes newline char.

            auto invariant() const
                -> bool
            { return not (m_current.p_first() == m_p_beyond_all and m_current.size() != 0); }

        public:
            auto at_end() const
                -> bool
            { return m_current.p_first() == m_p_beyond_all; }

            auto operator*() const
                -> String_view                          // Sans newline char.
            {
                auto const& v = m_current;
                return (0?0
                    : at_end()?     String_view()
                    :               String_view( v.p_first(), v.size() - 1 )
                    );
            }

            void advance()
            {
                if( at_end() )
                {
                    return;
                }
                const ptr_<const char> p_first = m_current.p_beyond();
                for( ptr_<const char> p = p_first; p != m_p_beyond_all; ++p )
                {
                    if( *p == '\n' )
                    {
                        const Size length = (1 + p) - p_first;
                        m_current = String_view( p_first, length );
                        return;
                    }
                }
                m_current = String_view( p_first, m_p_beyond_all - p_first );
            }

            friend auto operator==( ref_<const Iterator> a, ref_<const Iterator> b )
                -> bool
            {
                return
                    a.m_current.data() == b.m_current.data() and
                    a.m_current.size() == b.m_current.size();
            }

            Iterator():
                m_p_beyond_all(),
                m_current()
            {}

            Iterator( ref_<const String_view> text_view ):
                m_p_beyond_all( text_view.p_beyond() ),
                m_current( text_view.p_first(), 0 )
            { advance(); }
        };

        auto begin() const
            -> Iterator
        { return Iterator( m_view ); }

        auto end() const
            -> Iterator
        { return Iterator(); }

        Lines_ref( ref_<const String_view> text_view ):
            m_view( text_view )
        {}
    };

}  // namespace cppx
