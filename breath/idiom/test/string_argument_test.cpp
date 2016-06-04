// =========================================================================
//                       Copyright 2015 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/idiom/string_argument.hpp"

/////////
#include "breath/diagnostics/assert.hpp"
#define DO_TEST( x ) BREATH_ASSERT( x )
//////

int
main()
{
    // construction
    {
        std::string const   s( "test" );
        breath::string_argument
                            arg( s ) ;
        DO_TEST( arg.value() == "test" ) ;

        char const *        s2 = "test-2" ;
        breath::string_argument
                            arg2( s2 ) ;
        DO_TEST(arg2.value() == "test-2" ) ;
    }

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
