#pragma once
#include <stdlib/extension/type_builders.hpp>
#include <stdlib/string.hpp>
#include <stdlib/string_view.hpp>

namespace cppx
{
    using namespace stdlib::ext::type_builders;
    using std::string;
    using std::string_view;

    inline auto get_p_first( ref_<const string_view> view )
        -> ptr_<const char>
    { return view.data(); }

    inline auto get_p_beyond( ref_<const string_view> view )
        -> ptr_<const char>
    { return get_p_first( view ) + view.size(); }

    class String_view
        : public string_view
    {
    public:
        auto p_first() const
            -> ptr_<const char>
        { return get_p_first( *this ); }

        auto p_beyond() const
            -> ptr_<const char>
        { return get_p_beyond( *this ); }

        using string_view::basic_string_view;

        String_view(){}

        String_view( ref_<const string> s ):
            string_view( s.data(), s.size() )
        {}

        String_view( ref_<const string_view> other ):
            string_view( other )
        {}
    };

}  // namespace cppx
