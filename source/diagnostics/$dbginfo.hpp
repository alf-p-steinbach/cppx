// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
// intentionally no #pragma once

#undef CPPX_DBGINFO
#ifdef NDEBUG
#   define CPPX_DBGINFO( s )        []{}()
#else
#   define CPPX_DBGINFO( ... )      dbginfo( __VA_ARGS__ )
#endif

#if not defined( CPPX_NO_DOLLAR_NAMES ) and not defined( $dbginfo )
#   define  $dbginfo    CPPX_DBGINFO
#endif
