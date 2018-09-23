#include <cppx/band-aid/core-language/$with.hpp>
namespace{ int x = 42; }

#pragma warning( disable: 4505 )        // Unused function has been removed
static void foo()
{
    $with( int(42) ) { (void) _; }
}
