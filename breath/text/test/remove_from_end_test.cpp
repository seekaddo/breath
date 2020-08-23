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

#include "breath/text/remove_from_end.hpp"
#include "breath/testing/testing.hpp"
#include <iostream>

int                 test_remove_from_end() ;

namespace {

void do_tests()
{
    BREATH_CHECK( breath::remove_from_end( "hello world", "world" ) ==
                                                                    "hello " ) ;
    BREATH_CHECK( breath::remove_from_end( "",      "" ) == "" ) ;
    BREATH_CHECK( breath::remove_from_end( "dummy", "" ) == "dummy" ) ;
    BREATH_CHECK( breath::remove_from_end( "nel mezzo del", "cammin" ) ==
                                                              "nel mezzo del") ;
    BREATH_CHECK( breath::remove_from_end( "foo", "foo") == "" ) ;
    BREATH_CHECK( breath::remove_from_end( "foo", "xfoo") == "foo" ) ;

    //      Ensure everything works if the two arguments are the same
    //      string.
    // -----------------------------------------------------------------------
    std::string const   test( "test" ) ;
    BREATH_CHECK( breath::remove_from_end( test, test ) == "" ) ;
}

}

int
test_remove_from_end()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run( "remove_from_end()",
                                        { do_tests } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
