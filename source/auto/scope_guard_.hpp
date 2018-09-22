// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
#pragma once

#include <cppx/class-kind/No_copy.hpp>      // cppx::No_copy
#include <stdlib/utility.hpp>               // std::move

namespace cppx{
    using std::move;

    template< class Func >
    class Scope_guard_
        : public No_copy
    {
        Func    cleanup_;

    public:
        void dismiss() { cleanup_ = []{}; }

        ~Scope_guard_() { cleanup_(); }  // Intentionally no try-block.

        Scope_guard_( Func cleanup )
            noexcept( Func( move( cleanup ) ) )
            : cleanup_( move( cleanup ) )
        {}
    };

    template< class Func >
    auto make_scope_guard( Func cleanup )
        -> Scope_guard_<Func>
    { return Scope_guard_<Func>( move( cleanup ) ); }

}  // namespace cppx
