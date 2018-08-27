// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
#pragma once
#include <cppx/text/stdstring-util.hpp>
#include <stdlib/optional.hpp>          // std::optional
#include <stdlib/utility.hpp>           // std::enable_if_t
#include <stdlib/type_traits.hpp>       // std::is_same_v
#include <optional>
#include <utility>                      // std::move
#include <type_traits>

namespace cppx
{
    using std::string;
    using std::enable_if_t;
    using std::is_same_v;
    using std::move;
    using std::optional;

    class Source_location
    {
        string  m_filename;
        int     m_linenumber;
        int     m_character_position;       // -1 if none.
        string  m_function_name;            // Empty if none.

    public:
        auto filename() const           -> string   { return m_filename; }
        auto linenumber() const         -> int      { return m_linenumber; }
        auto character_position() const -> int      { return m_character_position; }
        auto function_name() const      -> string   { return m_function_name; }

        auto file_and_line() const
            -> string
        { return To_str() << "File “" << filename() << "” at line " << linenumber(); }

        auto file_line_and_pos() const
            -> string
        {
            To_str result;
            result << file_and_line();
            if( m_character_position != -1 )
            {
                result << " position " << m_character_position;
            }
            return move( result );
        }

        auto full_spec() const
            -> string
        {
            To_str result;
            result << file_line_and_pos();
            if( not m_function_name.empty() )
            {
                result << ", in function " << m_function_name;
            }
            return move( result );
        }

        operator string() const { return full_spec(); }

        auto make_short_message( ref_<const string> s ) const
            -> string
        { return To_str{} << function_name() << " - " << s; }

        auto make_verbose_message( ref_<const string> s ) const
            -> string
        { return To_str{} << full_spec() << " - " << s; }

        Source_location(
            string              filename,
            optional<int>       linenumber          = {},
            optional<int>       character_position  = {},
            optional<string>    function_name       = {}
            ):
            m_filename{ move( filename ) },
            m_linenumber{ linenumber.value_or( -1 ) },
            m_character_position{ character_position.value_or( -1 ) },
            m_function_name{ move( function_name ).value_or( "" ) }
        {}
    };

    inline auto to_string( ref_<const Source_location> loc )
        -> string
    { return loc.operator string(); }

}  // namespace cppx
