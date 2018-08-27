// Source encoding: UTF-8 (π is a lowercase Greek "pi" character).
#pragma once
#include <stdlib/c/assert.hpp>
#include <stdlib/utility.hpp>

namespace cppx {
    using std::forward;

    template< class Type >
    class Dynamically_instantiable;

    namespace impl {
        class Dynamic_allocation_restriction
        {
            template< class Type > friend class Dynamically_instantiable;
            struct Private_thing {};
            virtual void instantiable( Private_thing ) = 0; // Use `make_new()` to instantiate.

        public:
            virtual ~Dynamic_allocation_restriction() {}
        };
    }  // namespace impl

    class Is_dynamically_allocated
        : public virtual impl::Dynamic_allocation_restriction
    {
    public:
        ~Is_dynamically_allocated() override {}
    };

    template< class Type >
    class Dynamically_instantiable final
        : public Type
    {
        void instantiable( Is_dynamically_allocated::Private_thing ) override {}

        template< class... Args >
        Dynamically_instantiable( Args&&... args )
            : Type{ forward<Args>( args )... }
            , impl::Dynamic_allocation_restriction{}
        {}
    
    public:
        ~Dynamically_instantiable() override {}

        template< class... Args >
        static auto make_new( Args&&... args )
            -> Type*
        { return new Dynamically_instantiable<Type>{ forward<Args>( args )... }; }
    };

    template< class Type, class... Args >
    inline auto make_new( Args&&... args )
        -> Type*
    { return Dynamically_instantiable<Type>::make_new( forward<Args>( args )... ); }

}  // namespace cppx
