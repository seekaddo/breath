// =========================================================================
//                    Copyright 2016-2018 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/diagnostics/exception.hpp"
#include "breath/testing/testing.hpp"
#include <cstddef>
#include <cstring>
#include <exception>
#include <iostream>
#include <string>

void
test_throwability()
{
    try {
        throw breath::exception( "test" ) ;
        BREATH_CHECK( false ) ;
    } catch ( std::exception const & ) {
    }
}

void
test_what_message_handling()
{
    std::string const   very_long_string( 5 * 1024, 'A' ) ;
    breath::exception const
                        e( very_long_string ) ;

    //  The idea, here, is that std::strlen will crash if the string
    //  is not null-terminated.
    // --------------------------------------------------------------
    std::size_t const volatile
                        length = std::strlen( e.what() ) ;
    static_cast< void >( length ) ;
}

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
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run( { test_throwability,
                                          test_what_message_handling,
                                          test_copy } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
