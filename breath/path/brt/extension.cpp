// =========================================================================
//                       Copyright 2006 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
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
