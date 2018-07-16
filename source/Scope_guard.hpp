#pragma once

#include <cppx/class-kind/No_copy.hpp>      // cppx::No_copy

#include <functional>       // std::function
#include <utility>          // std::move

namespace cppx{
    using std::function;
    using std::move;

    class Scope_guard
        : public No_copy
    {
        function<void()>    cleanup_;

    public:
        void dismiss() { cleanup_ = []{}; }

        ~Scope_guard() { cleanup_(); }      // Intentionally no try-block here.

        Scope_guard( function<void()> cleanup )
            : cleanup_{ move( cleanup ) }
        {}
    };
}  // namespace cppx
