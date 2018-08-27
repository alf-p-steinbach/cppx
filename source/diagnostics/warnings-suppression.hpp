// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
#pragma once

#if defined( _MSC_VER )
#   define  CPPX_BEGIN_EXTERNAL     __pragma( warning( push, 0 ) )
#   define  CPPX_END_EXTERNAL       __pragma( warning( pop ) )
#else
#   define  CPPX_BEGIN_EXTERNAL
#   define  CPPX_END_EXTERNAL
#endif

#if defined( _MSC_VER )
#   pragma warning( disable: 4458 )        // C4458: declaration of 'i' hides class member
#   pragma warning( disable: 4099 )        // pdb not found
#endif
