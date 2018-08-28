// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
// Intentionally no `#pragma once`.
// Intentionally no qualification of `dbginfo`: it's supplied by client code.

#undef CPPX_DBGINFO
#ifdef NDEBUG
#   define $dbginfo( s )        []{}()
#else
#   define $dbginfo( ... )      dbginfo( __VA_ARGS__ )
#endif
