// =========================================================================
//                       Copyright 2008 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/text/trim_head.hpp"

#include <string>

// gps temp
#include "breath/diagnostics/assert.hpp"
#define DO_TEST( x ) BREATH_ASSERT( x )
////////////////

int
main()
{
    using breath::trim_head ;

    DO_TEST( trim_head( "" ) == "" ) ;
    DO_TEST( trim_head( " " ) == "" ) ;
    DO_TEST( trim_head( "\t" ) == "" ) ;
    DO_TEST( trim_head( " \t" ) == "" ) ;
    DO_TEST( trim_head( "\t " ) == "" ) ;


    DO_TEST( trim_head( "  abc" ) == "abc" ) ;
    DO_TEST( trim_head( "\t abc" ) == "abc" ) ;
    DO_TEST( trim_head( "abc a" ) == "abc a" ) ;

    DO_TEST( trim_head( "abcd", "ab" ) == "cd" ) ;
    DO_TEST( trim_head( "abcde", "badc" ) == "e" ) ;
    DO_TEST( trim_head( "a", "bcde" ) == "a" ) ;
    DO_TEST( trim_head( "abcd", "bce" ) == "abcd" ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
