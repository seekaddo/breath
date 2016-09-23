// =========================================================================
//                       Copyright 2008 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________
//
//!     \file
//!     \brief A thin wrapper around \c std::strftime().
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_wR9yYhDtICLHOJ6c2LmBkhMWoYoaeVkS
#define BREATH_GUARD_wR9yYhDtICLHOJ6c2LmBkhMWoYoaeVkS

#include "breath/idiom/maybe.hpp"
#include <string>

namespace breath {

class time_string_zone
{
public:
    enum zone
    {
        utc,
        local
    } ;

} ;


//      time_string
//      -----------
//
//!     This is a simple tool for simple and quick formatting needs.
//!     You should use a more complete solution for more complex needs
//!     (but don't underestimate the good old strftime() ;-)).
//!
//!     NOTE: document reentrancy issues (see C99, 7.23.3)
// ---------------------------------------------------------------------------
breath::maybe< std::string >
                    time_string( std::string const & format,
                                 time_string_zone::zone =
                                                    time_string_zone::utc ) ;
}
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
