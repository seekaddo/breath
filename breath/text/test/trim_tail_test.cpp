// =========================================================================
//                       Copyright 2008 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/text/trim_tail.hpp"
#include "breath/text/set_of_chars.hpp"

#include <string>

// gps temp
#include "breath/diagnostics/assert.hpp"
#define DO_TEST( x ) BREATH_ASSERT( x )
////////////////

int
main()
{
    using breath::trim_tail ;

    DO_TEST( trim_tail( "" ) == "" ) ;
    DO_TEST( trim_tail( " " ) == "" ) ;
    DO_TEST( trim_tail( "\t" ) == "" ) ;
    DO_TEST( trim_tail( " \t" ) == "" ) ;
    DO_TEST( trim_tail( "\t " ) == "" ) ;


    DO_TEST( trim_tail( "abc  " ) == "abc" ) ;
    DO_TEST( trim_tail( "abc \t" ) == "abc" ) ;
    DO_TEST( trim_tail( "abc a" ) == "abc a" ) ;

    DO_TEST( trim_tail( "abcd", breath::set_of_chars( "db" ) ) == "abc" ) ;
    DO_TEST( trim_tail( "abcd", breath::set_of_chars( "badc" ) ) == "" ) ;
    DO_TEST( trim_tail( "a", breath::set_of_chars( "bcde" ) ) == "a" ) ;
    DO_TEST( trim_tail( "abcd", breath::set_of_chars( "bce" ) ) == "abcd" ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
