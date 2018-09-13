// =========================================================================
//                    Copyright 2017-2018 Gennaro Prota
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

class incomplete_type ;

void do_tests()
{
    std::string const   s = breath::readable_type_name< incomplete_type >() ;
    BREATH_CHECK( s.find( "::incomplete_type" ) != s.npos ) ;

    BREATH_CHECK( breath::readable_type_name< int >() == "int" ) ;

    std::string const   s2 = breath::readable_type_name< int const &>() ;
    BREATH_CHECK( s2 == "int const&" || s2 == "int const &") ;

    std::string const   s3 = breath::readable_type_name< int volatile && >() ;
    BREATH_CHECK( s3 == "int volatile&&" || s3 == "int volatile &&") ;

    BREATH_CHECK( breath::readable_type_name< unsigned long >() ==
                                                             "unsigned long" ) ;
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
