// =========================================================================
//                       Copyright 2015 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/stream/format_saver.hpp"
#include "breath/testing/testing.hpp"
#include <iomanip>
#include <sstream>
#include <iostream>
#include <ostream>


void
check()
{
    using breath::format_saver ;
    std::stringstream   str ;
    {
        format_saver        saver( str );
        str.setf( std::ios::hex, std::ios::basefield ) ;
        str.fill( '0' ) ;
        str << std::setw( 2 ) << 15 ;
        BREATH_CHECK( str.str() == "0f" ) ;
    }
    BREATH_CHECK( (str.flags() & std::ios::hex) == 0 ) ;
    BREATH_CHECK( str.fill() == ' ' );
}

int
main()
{
    using namespace breath;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    test_runner::instance().run( { check } ) ;
}


// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
