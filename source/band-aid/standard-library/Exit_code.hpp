// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
#pragma once
#include <stdlib/c/stdlib.hpp>      // EXIT_...

namespace cppx{
    namespace impl {
        #if defined( _WIN32 )
            namespace winapi {
                const int error_invalid_function    = 1;                // Error code
                const int e_fail                    = 0x80004005;       // HRESULT
            }  // namespace winapi

            static_assert( EXIT_FAILURE == winapi::error_invalid_function, "!" );
            const int general_failure_code = winapi::e_fail;
        #else
            const int general_failure_code = EXIT_FAILURE;
        #endif
    }  // namespace impl

    struct Exit_code
    {
        enum Enum: int
        {
            success             = 0,
            failure             = impl::general_failure_code,
            cppstd_failure      = EXIT_FAILURE
        };
    };

    static_assert( Exit_code::success == EXIT_SUCCESS, "!" );
    static_assert( Exit_code::failure != 0, "!" );
    static_assert( Exit_code::cppstd_failure != 0, "!" );

}  // namespace cppx
