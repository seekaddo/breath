// =========================================================================
//                       Copyright 2017 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/stream/null_stream.hpp"
#include "breath/testing/testing.hpp"
#include <iostream>
#include <ostream>
#include <sstream>

void
check()
{
    {
        breath::null_stream s ;
        std::stringstream   ss ;
        static_cast< std::ostream & >( ss ).rdbuf( s.rdbuf() ) ;
        ss << "ignored" ;
        BREATH_CHECK( ss.str() == "" ) ;
    }
    {
        breath::null_stream s ;
        s << "ignored" ;
        BREATH_CHECK( s.good() ) ;
    }
    {
        breath::null_stream s ;
        int i ;
        s >> i ;
        BREATH_CHECK( s.eof() ) ;
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