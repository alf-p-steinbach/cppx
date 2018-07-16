#include <cppx/diagnostics/console-output.hpp>

#ifndef _WIN32
#   error This file is only meaningful for Microsoft Windows.
#endif

#include <wrapped-windows/windows-h.hpp>

namespace cppx{ namespace debug{

    namespace impl{
        void init_console( const bool ensure_new_line )
        {
            has_console() = (GetStdHandle( STD_ERROR_HANDLE ) != 0);
#ifdef NDEBUG
            (void) ensure_new_line;
#else
            if( not has_console() )
            {
                has_console() =
                    AttachConsole( ATTACH_PARENT_PROCESS )
                    or AllocConsole();
                if( has_console() )
                {
                    freopen( "con", "w", stderr );
                }
            }
            if( has_console() and ensure_new_line )
            {
                fprintf( stderr, "\n" );  fflush( stderr );
            }
#endif
        }
    }  // namespace impl

    void init_console() { impl::init_console( true ); }
    void init_console_no_new_line() { impl::init_console( false ); }

}}  // namespace cppx::debug
