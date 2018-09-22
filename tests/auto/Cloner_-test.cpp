#include <boost/test/unit_test.hpp>
#include <cppx/auto/Cloner_.hpp>
#include <utility>

namespace {
    struct S
    {
        static auto count() -> int& { static int c; return c; }

        S(){ ++count(); }
        S( const S& ) { ++count(); }
        S( S&& ) { ++count(); }
        virtual ~S() { --count(); }
    };

    struct Base{};
    struct Derived: Base, S {};
}

BOOST_AUTO_TEST_SUITE( Cloner_ )

    BOOST_AUTO_TEST_CASE( default_construction )
    {
        cppx::Cloner_<int> cloner;
        BOOST_TEST( cloner.p() == nullptr );
    }

    BOOST_AUTO_TEST_CASE( auto_cleanup )
    {
        BOOST_REQUIRE( S::count() == 0 );

        {
            cppx::Cloner_<S> cloner1( new S );
            BOOST_TEST( S::count() == 1 );
            cppx::Cloner_<S> cloner2 = cloner1.clone();
            BOOST_TEST( S::count() == 2 );
        }
        BOOST_TEST( S::count() == 0 );
    }

    BOOST_AUTO_TEST_CASE( auto_nonpolymorphic_cleanup )
    {
        BOOST_REQUIRE( S::count() == 0 );

        {
            cppx::Cloner_<Base> cloner1( new Derived );
            BOOST_TEST( S::count() == 1 );
            cppx::Cloner_<Base> cloner2 = cloner1.clone();
            BOOST_TEST( S::count() == 2 );
        }
        BOOST_TEST( S::count() == 0 );
    }

    BOOST_AUTO_TEST_CASE( assign_empty )
    {
        BOOST_REQUIRE( S::count() == 0 );

        cppx::Cloner_<S> cloner( new S );
        BOOST_TEST( S::count() == 1 );
        cloner = {};
        BOOST_TEST( S::count() == 0 );
    }

BOOST_AUTO_TEST_SUITE_END()
