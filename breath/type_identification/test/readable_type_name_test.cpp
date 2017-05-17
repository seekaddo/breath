// =========================================================================
//                       Copyright 2017 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/type_identification/readable_type_name.hpp"
#include "breath/testing/testing.hpp"

#include <iostream>
#include <ostream>
#include <string>

namespace {

void do_tests()
{
    BREATH_CHECK( breath::readable_type_name< int >() == "int" ) ;
    BREATH_CHECK( breath::readable_type_name< unsigned long >() ==
                                                             "unsigned long" ) ;
    BREATH_CHECK( breath::readable_type_name< std::string >() == "string" ) ;
}

}

int
main()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run( { do_tests } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
