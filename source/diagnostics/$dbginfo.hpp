// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
// intentionally no #pragma once

#undef CPPX_DBGINFO
#ifdef NDEBUG
#   define $dbginfo( s )        []{}()
#else
#   define $dbginfo( ... )      dbginfo( __VA_ARGS__ )
#endif
