// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/text/from_string.hpp"
#include "breath/testing/testing.hpp"
#include "breath/iteration/begin_end.hpp"
#include <iostream>
#include <ostream>

namespace {

void do_tests()
{
    BREATH_CHECK( breath::from_string< int >( "12" ) == 12 )
    //BREATH_CHECK_THROW( from_string<int>( "12 1" ) )
}

}

int
main()
{
    using namespace breath;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    test_descriptor     desc[] =
    {
        do_tests
    };

    test_runner::instance().run( begin( desc ), end( desc ) ) ;

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
