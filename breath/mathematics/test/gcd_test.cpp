// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/mathematics/gcd.hpp"
#include "breath/testing/testing.hpp"
#include <iostream>

namespace {

void
do_check()
{
    struct
    {
        int a ;
        int b ;
        int gcd ;
    } constexpr         table[] = {
         0,  0, 0,
        -1, -1, 1,
        -1,  1, 1,
         1, -1, 1,
         1,  1, 1,
        12,  4, 4,
        36, 24, 12,
        30,-25, 5,
        -3,  0, 3,
         0, -3, 3,
         3, -3, 3
    } ;

    for ( auto const & t : table ) {
        BREATH_CHECK( breath::gcd( t.a, t.b ) == t.gcd ) ;
        BREATH_CHECK( breath::gcd( t.b, t.a ) == t.gcd ) ;

    }

}

}

int
main()
{
    using namespace breath;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    test_runner::instance().run( { do_check } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
