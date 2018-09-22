// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
#pragma once
#include <cppx/auto/Scope_guard_.hpp>

namespace cppx
{
    template< class Func >
    class Forced_cleanup_:
        private Scope_guard_<Func>
    {
    public:
        using Scope_guard_<Func>::Scope_guard_;
    };

    template< class Func >
    auto make_forced_cleanup( Func cleanup )
        -> Forced_cleanup_<Func>
    { return Forced_cleanup_<Func>( move( cleanup ) ); }
}  // namespace cppx
