// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
#pragma once
#include <cppx/band-aid/standard-library/type-traits.hpp>   // cppx::is_base_and_derived
#include <cppx/type-builders.hpp>
#include <stdlib/utility.hpp>                               // std::(enable_if_t, move)

namespace cppx
{
    using std::enable_if_t;
    using std::move;

    template< class Referent>
    class Temp_ref_
    {
        template< class > friend class Temp_ref_;

        Referent*   m_p;

    public:
        auto referent() const
            -> Referent&&
        { return move( *m_p ); }

        Temp_ref_( Referent&& o ):
            m_p( &o )
        {}

        Temp_ref_( ref_<const Referent> ) = delete;

        template< class Other
            , class = enable_if_t< is_base_and_derived< Referent, Other > >
            >
        Temp_ref_( Temp_ref_<Other>&& other ):
            m_p( other.m_p )
        {}
    };

    template< class Referent >
    auto object( const Temp_ref_<Referent> temp )
        -> Referent
    { return temp.referent(); }

}  // namespace cppx
