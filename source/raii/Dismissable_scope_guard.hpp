// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
#pragma once

#include <cppx/class-kind/No_copy.hpp>      // cppx::No_copy

#include <stdlib/functional.hpp>            // std::function
#include <stdlib/utility.hpp>               // std::move

namespace cppx{
    using std::function;
    using std::move;

    class Dismissable_scope_guard
        : public No_copy
    {
        function<void()>    cleanup_;

    public:
        void dismiss() { cleanup_ = []{}; }

        ~Dismissable_scope_guard() { cleanup_(); }  // Intentionally no try-block.

        Dismissable_scope_guard( function<void()> cleanup )
            : cleanup_{ move( cleanup ) }
        {}
    };
}  // namespace cppx
