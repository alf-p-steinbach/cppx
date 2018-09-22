// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
#pragma once
#include <cppx/band-aid/core-language/type-builders.hpp>
#include <exception>            // std::(rethrow_exception)
#include <stdexcept>            // std::(exception_ptr)

namespace cppx
{
    using std::exception_ptr;
    using std::rethrow_exception;

    namespace impl
    {
        inline auto stored_ptr()
            -> ref_<exception_ptr>
        {
            static exception_ptr the_stored_ptr;
            return the_stored_ptr;
        }
    }

    inline auto replace_stored_x_with( ref_<const exception_ptr> p )
        -> exception_ptr
    {
        exception_ptr original = impl::stored_ptr();
        impl::stored_ptr() = p;
        return original;
    }

    void clear_stored_x()
    {
        impl::stored_ptr() = nullptr;
    }

    inline void rethrow_any_stored_x()
    {
        const exception_ptr p = impl::stored_ptr();
        if( p != nullptr )
        {
            impl::stored_ptr() = nullptr;
            rethrow_exception( p );
        }
    }
}
