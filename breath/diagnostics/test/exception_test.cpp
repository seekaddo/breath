// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/diagnostics/exception.hpp"
#include "breath/testing/testing.hpp"
#include <cstring>
#include <iostream>

void
test_copy()
{
    breath::exception   ex( "test" ) ;
    breath::exception   ex2( ex ) ;
    BREATH_CHECK( std::strcmp( ex.what(), ex2.what() ) == 0 ) ;

    breath::exception   ex3 ;
    ex3 = ex ;
    BREATH_CHECK( std::strcmp( ex.what(), ex3.what() ) == 0 ) ;
}

int
main()
{
    using namespace breath;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run( { test_copy } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
