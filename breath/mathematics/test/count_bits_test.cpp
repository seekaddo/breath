// =========================================================================
//                       Copyright 2017 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/mathematics/count_bits.hpp"
#include "breath/testing/testing.hpp"
#include <climits>
#include <cstddef>
#include <iostream>
#include <ostream>

namespace {

template< typename T >
std::size_t
trivially_count_bits( T t )
{
    std::size_t         count = 0 ;
    while ( t != 0 ) {
        ++ count ;
        t &= ( t - 1 ) ;
    }
    return count ;
}

void check()
{
    for ( unsigned i = 0 ; i <= UCHAR_MAX ; ++ i ) {
        BREATH_CHECK( breath::count_bits( i ) == trivially_count_bits( i ) ) ;
    }
}

void check2()
{
    unsigned long       n = 0b010'110'011'011;
    BREATH_CHECK( breath::count_bits( n ) == 7 ) ;
}

}

int
main()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run( { check, check2 } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
