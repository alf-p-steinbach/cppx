#pragma once
#include <cppx/text/stdstring-util.hpp>
#include <stdlib/optional.hpp>          // std::optional
#include <stdlib/utility.hpp>           // std::enable_if_t
#include <stdlib/type_traits.hpp>       // std::is_same_v
#include <optional>
#include <utility>
#include <type_traits>

#ifndef CPPX_NO_DOLLAR_NAMES
#   define  $source_location    CPPX_SOURCE_LOCATION
#endif

#define CPPX_SOURCE_LOCATION() \
    cppx::Source_location{ __FILE__, __LINE__, {}, __func__ }

namespace cppx
{
    using std::string;
    using std::enable_if_t;
    using std::is_same_v;
    using std::optional;

    class Source_location
    {
        string  m_function_name;            // Empty if none.
        string  m_filename;
        int     m_linenumber;
        int     m_character_position;       // -1 if none.

    public:
        auto function_name() const      -> string   { return m_function_name; }
        auto filename() const           -> string   { return m_filename; }
        auto linenumber() const         -> int      { return m_linenumber; }
        auto character_position() const -> int      { return m_character_position; }

        auto file_and_line() const
            -> string
        { return To_str{} << "File “" << filename() << "” at line " << linenumber(); }

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
            const int           linenumber,
            optional<int>       character_position  = {},
            optional<string>    function_name       = {}
            )
            : m_function_name{ move( function_name ).value_or( "" ) }
            , m_filename{ move( filename ) }
            , m_linenumber{ linenumber }
            , m_character_position{ character_position.value_or( -1 ) }
        {}
    };

    inline auto to_string( ref_<const Source_location> loc )
        -> string
    { return loc.operator string(); }

}  // namespace cppx
