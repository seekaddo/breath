// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/mathematics/lcm.hpp"
#include "breath/testing/testing.hpp"
#include <iostream>

namespace {

void
do_check()
{
    constexpr struct
    {
        int a ;
        int b ;
        int lcm ;
    }                   table[] = {
        {  0,  0,  0 },
        { -1,  0,  0 },
        { -3,  0,  0 },
        { 18, 24, 72 },
        { 23 * 5, 12 * 5, 23 * 12 * 5 },
        { 31 * 7, 7 * 2, 31 * 7 * 2 }
    } ;

    for ( auto const & t : table ) {
        BREATH_CHECK( breath::lcm( t.a, t.b ) == t.lcm ) ;
        BREATH_CHECK( breath::lcm( t.b, t.a ) == t.lcm ) ;
    }

}

}

int
main()
{
    using namespace breath;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run( { do_check } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
