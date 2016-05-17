#include "breath/memory/auto_array.hpp"
#include "breath/testing/testing.hpp"
#include <iostream>
#include <vector>

namespace {

breath::auto_array< int >
f()
{
    return breath::auto_array< int >( new int[ 3 ]{ 0, 1, 2 } ) ;
}

void
check_move_semantics()
{
    // Check that the move constructor is in effect.
    //
    breath::auto_array< int > a = f() ;
    for ( int i = 0 ; i < 3 ; ++i ) {
        BREATH_CHECK( a.get()[ i ] == i ) ;
    }
    // Check also the move assignment operator.
    // NOTE: this is bad code, with a hard-coded constant (3) and
    // hard-coded values (plus, code repetition).
    a = f() ;
    for ( int i = 0 ; i < 3 ; ++i ) {
        BREATH_CHECK( a.get()[ i ] == i ) ;
    }
}

void
check_non_move_constructors()
{
    breath::auto_array< std::string >
                        a( new std::string[ 2 ]{ "foo", "bar" } ) ;
    BREATH_CHECK( a.get()[ 0 ] == "foo" ) ;
    BREATH_CHECK( a.get()[ 1 ] == "bar" ) ;

    breath::auto_array< double > deflt ;
    BREATH_CHECK( deflt.get() == nullptr ) ;

    breath::auto_array< char > n( nullptr ) ;
    BREATH_CHECK( n.get() == nullptr ) ;

}

void
check_reset()
{
    // We can''t check that buffers are destroyed properly. This can
    // only be ascertain by code inspection on the reset() function.
    // The case reset( nullptr ) is an important one.
    //
    breath::auto_array< std::vector< int > >
                        a( new std::vector< int >[ 100 ] ) ;
    a.reset( new std::vector< int >[ 5 ]) ;
    a.reset( nullptr ) ;
}

}

int
main()
{
    using namespace breath;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    test_runner::instance().run( { check_move_semantics,
                                   check_non_move_constructors,
                                   check_reset                 } ) ;
}