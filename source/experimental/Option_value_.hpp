#pragma once
#include <cppx/stdlib-wrappers/type-traits.hpp>
#include <stdlib/extension/type_builders.hpp>
#include <stdlib/tuple.hpp>

// Preferably use this only in namespace `::name`
#define CPPX_DEFINE_NAMETYPE( name ) \
    using name = struct name ## _tag_struct volatile*

namespace cppx
{
    using namespace stdlib::ext::type_builders;     // ref_ etc.

    namespace options_def
    {
        using std::enable_if_t;
        using std::move;
        using std::tuple;
        
        struct Options_class_tag {};

        template< class Value, class Key >
        struct Option_value_
            : virtual Options_class_tag
        {
            Value   value;
            
            Option_value_() = default;

            Option_value_( Key, Value v )
                : value( move( v ) )
            {}
        };

        // Reads like `Opt{} | value_of_<Blah>( 123 ) | value_of_<Gnorbl>( '@' )`.
        template< class Key, class Value >
        auto value_of_( Value v )
            -> Option_value_<Value, Key>
        { return {Key{}, move( v )}; }

        template< class Options, class Key, class Value >
        auto set_value_in( ref_<Options> o, Option_value_<Value, Key> value )
            -> ref_<Options>
        {
            static_cast<ref_<Option_value_<Value, Key>>( o ) = move( value );
            return o;
        }

        template< class Value >
        void unset_value_in_variable( ref_<Value> var, ref_<const Value> value )
        {
        }

        //template< class Options, class Key, class Value >
        //auto unset_value_in( ref_<Options> o, ref_<const Option_value_<Value, Key>> value )
        //    -> ref_<Options>
        //{
        //    unset_value_in_variable( static_cast<ref_<Option_value_<Value, Key>>( o ), value );
        //    return o;
        //}

        //template< class Options, class... Items >
        //auto set_values_in( Options& o, ref_<const tuple<Items...>> values )
        //    -> Options&
        //{
        //    if constexpr( sizeof...( Items ) > 0 )
        //    {
        //    }
        //    //static_cast<Option_value_<Value, Key>&>( o ) = move( value );
        //    return o;
        //}

        namespace impl
        {
            template< class Key, class Value >
            auto value_type( Option_value_<Value, Key> const& ) -> Value;
        }

        template< class Key, class Options
            , class = enable_if_t< is_base_and_derived< Options_class_tag, Options > >
            >
        auto const& value_ref( Options const& o )
        {
            using Value = decltype( impl::value_type<Key>( o ) );
            return static_cast<Option_value_<Value, Key> const&>( o ).value;
        }


        //------------------------------------------------------------------
        // Syntactic sugar

        template< class Options, class Key, class Value >
        auto operator+( Options&& o, Option_value_<Value, Key> value )
            -> Options&&
        { return move( set_value_in( o, value ) ); }

        template< class Options, class Key, class Value >
        auto operator+( Options& o, Option_value_<Key, Value> value )
            -> Options
        {
            Options copy = o;
            set_value_in( copy, value );
            return copy;
        }

        template< class Key, class Options
            , class = enable_if_t< is_base_and_derived< Options_class_tag, Options > >
            >
        auto& item( Options const& o )  // -> inferred
        { return value_ref<Key>( o ); }
    }  // namespace options_def

    namespace options_shortname
    {
        using options_def::Option_value_;
        using options_def::value_of_;

        template< class Key, class Value >
        auto _( Value v )
            -> Option_value_<Value, Key>
        { return value_of_<Key>( move( v ) ); }
    }

    inline namespace options
    {
        using options_def::Option_value_;
        using options_def::value_of_;
        using options_def::set_value_in;
        using options_def::value_ref;
        using options_def::operator+;
        using options_def::item;
    }  // namespace options
}  // namespace cppx


#if 0
// Example usage:

namespace name
{
    CPPX_DEFINE_NAMETYPE( Position );
    CPPX_DEFINE_NAMETYPE( Speed );
    CPPX_DEFINE_NAMETYPE( Speed );       // Just to show that multiple defs are OK.
}  // namespace name

struct Base_options
    : cppx::Option_value_<int, name::Position>
{};

struct Derived_options
    : Base_options
    , cppx::Option_value_<int, name::Speed>
{};

#include <iostream>
auto main()
    -> int
{
    using namespace std;
    using namespace name;
    using namespace cppx::options;

    auto const o = Derived_options{} | value_of_<Position>( 1 ) | value_of_<Speed>( 2 );
    cout << "Position " << item<Position>( o ) << endl;
    cout << "Speed " << item<Speed>( o ) << endl;
}
#endif
