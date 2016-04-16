// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
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
    std::istringstream ss( s ) ;
    if ( !( ss >> t ) || !( ss >> std::ws ).eof() ) {
        throw exception( "from_string error" ) ;
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
