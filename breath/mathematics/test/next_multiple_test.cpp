// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/mathematics/next_multiple.hpp"
#include "breath/testing/testing.hpp"
#include <climits>
#include <ostream>
#include <iostream>

void
check()
{
    using               breath::next_multiple ;

    {
        BREATH_CHECK( next_multiple( 8, 3 ) == 9 ) ;
        BREATH_CHECK( next_multiple( 9, 3 ) == 9 ) ;
        BREATH_CHECK( next_multiple(-8, 3 ) == -6 ) ;
        BREATH_CHECK( next_multiple( -11, 4 ) == -8 ) ;
    }
}

int
main()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run( { check } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
