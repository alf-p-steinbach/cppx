#include <cppx/text/as_text_.hpp>
namespace cppx
{
    template auto as_text_<char>( ref_<const char> ) -> basic_string<char>;
    template auto as_text_<wchar_t>( ref_<const wchar_t> ) -> basic_string<wchar_t>;
}
