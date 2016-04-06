// =========================================================================
//                    Copyright 2008-2015 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#ifndef BREATH_GUARD_rAf6FomrfEupsrKlsZvh9xwbNaeg8pxp
#define BREATH_GUARD_rAf6FomrfEupsrKlsZvh9xwbNaeg8pxp

#include "breath/text/set_of_chars.hpp"
#include <string>

namespace breath {

std::string         trim_tail( std::string const & str ) ;

std::string         trim_tail( std::string const &  str,
                               set_of_chars const & to_remove ) ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
