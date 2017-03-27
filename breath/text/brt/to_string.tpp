// =========================================================================
//                       Copyright 2008 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/diagnostics/exception.hpp"
#include <sstream>

namespace breath {

template <typename OutputStreamable >
std::string
to_string( OutputStreamable const & object )
{
    std::ostringstream  ss ;
    ss << object ;
    if ( ss.fail() ) {
        throw breath::exception( "error in to_string()" ) ;
    }
    return ss.str() ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
