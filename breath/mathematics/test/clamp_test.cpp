// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/mathematics/clamp.hpp"
#include "breath/testing/testing.hpp"
#include <iostream>
#include <ostream>
#include <climits>
#include <vector>
#include <cstddef>

namespace {

void
check()
{
    struct
    {
        int value ;
        int low ;
        int hi ;
        int result ;
    } const             table[] =
    {
        { 1, 5, 8, 5 },
        { 7, 5, 8, 7 },
        { 9, 5, 8, 8 },
        { 3, INT_MIN, INT_MIN, INT_MIN },
        { 1, INT_MIN, INT_MAX, 1 },
        { 5, INT_MAX, INT_MAX, INT_MAX },
        { 3, 3, 3, 3 }
    } ;

    for ( auto const & item : table ) {
        BREATH_CHECK( breath::clamp( item.value, item.low, item.hi )
                                                             == item.result ) ;
    }
}

void
check2()
{
    // Check that a reference to the first argument is returned when the
    // first argument is equivalent to one of the bounds.
    //
    int const           a = 5 ;
    int const           low = 5 ;
    int const           high = 10 ;
    
    BREATH_CHECK( & breath::clamp( a, low, high ) == & a ) ;

    int const           a2 = 10 ;

    BREATH_CHECK( & breath::clamp( a2, low, high) == & a2 ) ;
}

void
check_clamp_range()
{
    std::vector< int >  v { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 } ;
    breath::clamp_range( v.cbegin(), v.cend(), v.begin(), 5, 8 ) ;
    std::vector< int >  result { 5, 5, 5, 5, 5, 6, 7, 8, 8, 8 } ;
    for ( std::size_t i = 0; i < v.size() ; ++ i ) {
        BREATH_CHECK( v[ i ] == result[ i ] );
    }
}

}

int
main()
{
    using namespace breath;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    test_runner::instance().run( { check, check2, check_clamp_range } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
