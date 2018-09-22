// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
#pragma once
#include <cppx/band-aid/core-language/type-builders.hpp>
#include <stdlib/locale.hpp>        // std::ctype
#include <stdlib/string.hpp>        // std::(basic_string, string, wstring)

#include <iostream>                 // wclog

namespace cppx{ namespace debug{
    using std::basic_string;
    using std::ctype;
    using std::clog;
    using std::endl;
    using std::string;
    using std::wclog;
    using std::wstring;

    extern void init_console();
    extern void init_console_no_new_line();

    #if not defined( CPPX_NO_AUTO_DEBUG_CONSOLE )
        static const bool debug_console_initialized = []() -> bool
        {
            init_console();     // OK with multiple calls.
            return true;
        }();
    #endif
    
    namespace impl {
        inline auto has_console()
            -> bool&
        {
            static bool value;
            return value;
        }
    }  // namespace impl

    inline auto has_console()
        -> bool
    { return impl::has_console(); }

    inline void put_line( ref_<const string> s )
    {
        clog << s << endl;
    }
    
    inline void put_line( ref_<const wstring> s )
    {
        wclog << s << endl;
    }
    
    namespace impl {
        template< class Char >
        inline void info_( ref_<const basic_string<Char>> s )
        {
            if( not has_console() or s.empty() ) { return; }

            using namespace std;
            static const auto indent = basic_string<Char>( 4, Char( ' ' ) );
            basic_string<Char> formatted = indent;
            for( const Char ch : s )
            {
                formatted += ch;
                if( ch == Char( '\n' ) ) { formatted += indent; }
            }
            formatted[0] = Char( '*' );
            put_line( formatted );
        }
    }  // namespace impl
    
    inline void info( ref_<const string> s ) { impl::info_<char>( s ); }
    inline void info( ref_<const wstring> s ) { impl::info_<wchar_t>( s ); }

}}  // namespace cppx::debug
