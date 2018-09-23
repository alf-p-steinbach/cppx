#include <cppx/diagnostics/$dbginfo.hpp>

namespace
{
    void dbginfo(...) {}
    auto dummy = ($dbginfo( 42 ), true);
}
