#pragma once
#include <cppx/class-kind/No_move.hpp>
#include <cppx/class-kind/No_copy.hpp>

namespace cppx{

    class No_copy_or_move
        : public No_copy
        , public No_move
    {};

}  // namespace cppx
