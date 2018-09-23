#include <cppx/band-aid/core-language/integral-types.hpp>

namespace
{
    template< class... > struct Use_{};
    using The_types = Use_<cppx::Byte, cppx::Size, cppx::Unsigned_size, cppx::Index, cppx::Unsigned_index>;

    int x = 42;
}
