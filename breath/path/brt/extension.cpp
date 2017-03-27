// =========================================================================
//                       Copyright 2006 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/path/extension.hpp"

namespace breath {

std::string
extension( std::string const & path )
{
    auto const          pos = path.rfind( '.' ) ;
    return pos == std::string::npos
        ? ""
        : path.substr( pos )
        ;
}


}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
