#pragma once

namespace cppx {

    class No_move
    {
        No_move( No_move&& ) = delete;
        auto operator=( No_move&& ) -> No_move& = delete;
    public:
        auto operator=( No_move const& ) -> No_move& = default;
        No_move() = default;
        No_move( No_move const& ) = default;

    };

}  // namespace cppx
