// =========================================================================
//                       Copyright 2008 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/text/begins_with.hpp"

#include <string>

// gps temp
#include "breath/diagnostics/assert.hpp"
#define DO_TEST( x ) BREATH_ASSERT( x )
////////////////

int
main()
{
    using breath::begins_with ;

    DO_TEST(   begins_with( "",  ""  ) ) ;
    DO_TEST(   begins_with( "a", ""  ) ) ;
    DO_TEST(   begins_with( "a", "a" ) ) ;
    DO_TEST( ! begins_with( "",  "a" ) ) ;
    DO_TEST( ! begins_with( "a", "ab" ) ) ;

    // some space tests
    DO_TEST(   begins_with( " a",  " "   ) ) ;
    DO_TEST(   begins_with( " a  ", " "   ) ) ;
    DO_TEST(   begins_with( "  a", "  "  ) ) ;
    DO_TEST( ! begins_with( " a",  "  "  ) ) ;
    DO_TEST( ! begins_with( " a",  "a"   ) ) ;
    DO_TEST( ! begins_with( "          ", "\t" ) ) ;

    DO_TEST(   begins_with( "abc", "ab"   ) ) ;
    DO_TEST( ! begins_with( "bcd", "abcd" ) ) ;

    // check that embedded NULs are handled correctly
    std::string         s ;
    s.push_back( 'a' );
    s.push_back( '\0' );
    s.push_back( 'b' );

    std::string         t ;
    t.push_back( '\0' ) ;
    DO_TEST( !begins_with( s, t) ) ;
    t = "a" ;
    t.push_back( '\0' );
    DO_TEST( begins_with( s, t ) );
    DO_TEST( begins_with( s, s ) );
    DO_TEST( begins_with( s, t ) );

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
