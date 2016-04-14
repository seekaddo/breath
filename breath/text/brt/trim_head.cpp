// =========================================================================
//                       Copyright 2008 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/text/trim_head.hpp"

namespace breath {

std::string
trim_head( std::string const & source, std::string const & to_remove )
{
    auto const          pos =
        source.find_first_not_of( to_remove ) ;
    return pos == std::string::npos
        ? ""
        : std::string( source, pos )
        ;


}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
