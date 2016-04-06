// =========================================================================
//                    Copyright 2013-2015 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/text/ends_with.hpp"
#include <algorithm>
#include <string>

namespace breath {

// note: if with.length() == 0 this always returns true
bool
ends_with( std::string const & str, std::string const & with )
{
    auto const          sz( with.size() ) ;
    return str.size() >= sz
        && std::equal( with.begin(), with.end(), str.end() - sz ) ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
