// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
//
// _________________________________________________________________________

#include "breath/diagnostics/exception.hpp"
#include <sstream>
#include <istream>

namespace breath {

template< typename T >
T
from_string( std::string const & s )
{
    T t ;
    std::istringstream  ss( s ) ;
    if ( !( ss >> t ) || !( ss >> std::ws ).eof() ) {
        throw breath::exception( "error in from_string()" ) ;
    }
    return t ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
