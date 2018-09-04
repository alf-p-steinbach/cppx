// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
#pragma once
#include <cppx/raii/Dismissable_scope_guard.hpp>

namespace cppx
{
    class Scope_guard:
        private Dismissable_scope_guard
    {
    public:
        using Dismissable_scope_guard::Dismissable_scope_guard;
    };
}
