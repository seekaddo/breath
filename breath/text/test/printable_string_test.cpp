// =========================================================================
//                       Copyright 2015 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/text/printable_string.hpp"
#include <sstream>
///
#include "breath/diagnostics/assert.hpp"
#define DO_TEST( x )  BREATH_ASSERT( x )
//////

int
main()
{
    using breath::printable_string ;

    {
        printable_string    p = nullptr ;
        std::ostringstream  ss ;
        ss << p ;
        DO_TEST( ss.str() == "(null)" ) ;
    }

    {
        printable_string    p = "\'\"\?\\\a\b\f\n\r\t\v\x1\xA0\xFF" ;
        std::ostringstream  ss ;
        ss << p ;
        DO_TEST( ss.str() == "\"'\\\"\\?\\\\\\a\\b\\f\\n\\r\\t\\v\\x01\\xa0\\xff\"") ;
    }

    {
        printable_string    no_trigraph = "\?\?!" ;
        std::ostringstream  ss ;
        ss << no_trigraph ;
        DO_TEST( ss.str() == "\"\\?\\?!\"" ) ;
    }

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
