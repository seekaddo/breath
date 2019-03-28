// =========================================================================
//                       Copyright 2008 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/text/split.hpp"

#include <string>
#include <vector>

// gps temp
#include "breath/diagnostics/assert.hpp"
#define DO_TEST( x ) BREATH_ASSERT( x )
////////////////

int
main()
{
    using               breath::split ;

    {
        std::string         s ;
        std::string         delimiters = { '\0' } ;
        std::vector< std::string >
                            v = split( s, delimiters) ;
        DO_TEST( v.size() == 0 ) ;
    }

    {
        std::string         s( "abcde" ) ;
        std::string         delimiters = { '\0' } ;
        std::vector< std::string > v = split( s, delimiters ) ;

        DO_TEST( v.size() == 1 ) ;
        DO_TEST( v[ 0 ] == "abcde" ) ;
    }

    {
        std::string         s( "string1" ) ;
        s.push_back( 'X' ) ;
        s += "string2" ;
        s.push_back( 'Y' ) ;
        s += "string3" ;
        std::vector< std::string > v = split( s, "XY" ) ;

        DO_TEST( v.size() == 3 ) ;
        DO_TEST( v[ 0 ] == "string1" ) ;
        DO_TEST( v[ 1 ] == "string2" ) ;
        DO_TEST( v[ 2 ] == "string3" ) ;
    }

    {
        std::string         s( "string1" ) ;
        s.push_back( 'A' ) ;
        s += "string2" ;
        s.push_back( 'B' ) ;
        s += "string3" ;
        s.push_back( 'C' ) ;
        std::vector< std::string > v = split( s, "ABC" ) ;

        DO_TEST( v.size() == 3 ) ;
        DO_TEST( v[ 0 ] == "string1" ) ;
        DO_TEST( v[ 1 ] == "string2" ) ;
        DO_TEST( v[ 2 ] == "string3" ) ;
    }

    {
        std::string         s( "string1" ) ;
        s.push_back( '\0' ) ;
        s.push_back( '\0' ) ;
        s += "string3" ;
        std::string         delimiters = { '\0' } ;
        std::vector< std::string > v = split( s, delimiters ) ;
        DO_TEST( v.size() == 3 ) ;
        DO_TEST( v[ 0 ] == "string1" ) ;
        DO_TEST( v[ 1 ].size() == 0 ) ;
        DO_TEST( v[ 2 ] == "string3" ) ;
    }

    {
        std::string const   only_delimiters( "x" ) ;
        std::string const   delimiters = only_delimiters ;
        std::vector< std::string > const
                            v = split( only_delimiters, delimiters ) ;
        DO_TEST( v.size() == 1 ) ;
        DO_TEST( v[ 0 ] == "" ) ;
    }
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
