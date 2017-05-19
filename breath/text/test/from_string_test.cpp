// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/text/from_string.hpp"
#include "breath/testing/testing.hpp"
#include <iostream>
#include <ostream>
#include <string>

namespace {

void do_tests()
{
    BREATH_CHECK_THROW( breath::from_string< int >( "   " ) ) ;
    BREATH_CHECK( breath::from_string< int >( "12" ) == 12 ) ;
    BREATH_CHECK( breath::from_string< int >( "12   \t" ) == 12 ) ;
    BREATH_CHECK_THROW( breath::from_string< int >( "12 1" ) ) ;
    BREATH_CHECK( breath::from_string< char >( "a" ) == 'a' ) ;
    BREATH_CHECK_THROW( breath::from_string< char >( "ab" ) ) ;
    BREATH_CHECK( breath::from_string< double >( "1.2" ) == 1.2 ) ;

    BREATH_CHECK( breath::from_string< std::string >( " test " ) == " test " ) ;
    BREATH_CHECK( breath::from_string< std::string >( "" ) == "" ) ;
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
