// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
#pragma once

namespace cppx {

    class No_copy
    {
        No_copy( No_copy const& ) = delete;
        auto operator=( No_copy const& ) -> No_copy& = delete;
    public:
        auto operator=( No_copy&& ) -> No_copy& = default;
        No_copy() = default;
        No_copy( No_copy&& ) = default;
    };

}  // namespace cppx
