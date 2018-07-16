#pragma once
#include <cppx/text/stdstring-util.hpp>
#include <stdlib/utility.hpp>           // std::enable_if_t
#include <stdlib/type_traits.hpp>       // std::is_same_v

#ifndef CPPX_NO_DOLLAR_NAMES
#   define  $source_location    CPPX_SOURCE_LOCATION
#endif

#define CPPX_SOURCE_LOCATION() \
    cppx::Source_location{ __FUNCTION__, __FILE__, __LINE__ }

namespace cppx
{
    using std::string;
    using std::enable_if_t;
    using std::is_same_v;

    class Source_location
    {
        string  m_function_name;
        string  m_filename;
        int     m_linenumber;

    public:
        auto function_name() const  -> string   { return m_function_name; }
        auto filename() const       -> string   { return m_filename; }
        auto linenumber() const     -> int      { return m_linenumber; }

        auto full_spec() const
            -> string
        {
            return To_str{}
                << function_name()
                << " [in “" << filename() << "” at line " << linenumber() << "]";
        }

        operator string() const { return function_name(); }

        auto message( ref_<const string> s ) const
            -> string
        { return To_str{} << function_name() << " - " << s; }

        auto verbose_message( ref_<const string> s ) const
            -> string
        { return To_str{} << full_spec() << " - " << s; }

        Source_location( string function_name, string filename, const int linenumber )
            : m_function_name{ move( function_name ) }
            , m_filename{ move( filename ) }
            , m_linenumber{ linenumber }
        {}
    };

    inline auto to_string( ref_<const Source_location> loc )
        -> string
    { return loc.function_name(); }

}  // namespace cppx
