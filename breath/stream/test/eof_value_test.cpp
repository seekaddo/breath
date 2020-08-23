// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2017 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/stream/eof_value.hpp"
#include "breath/testing/testing.hpp"
#include <iostream>
#include <sstream>

int                 test_eof_value() ;

namespace {

void
check()
{
    {
        std::stringstream   ss ;
        BREATH_CHECK( breath::is_eof_value( ss.peek(), ss ) ) ;
        BREATH_CHECK( breath::is_eof_value( breath::eof_value( ss ), ss ) ) ;
    }
}

}

int
test_eof_value()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run( "eof_value()", { check } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
