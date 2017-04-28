// =========================================================================
//                       Copyright 2017 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/stream/eof_value.hpp"
#include "breath/testing/testing.hpp"
#include <iostream>
#include <ostream>
#include <sstream>

void
check()
{
    {
        std::stringstream   ss ;
        BREATH_CHECK( breath::is_eof_value( ss.peek(), ss ) ) ;
        BREATH_CHECK( breath::is_eof_value( breath::eof_value( ss ), ss ) ) ;
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
