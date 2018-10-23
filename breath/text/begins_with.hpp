// =========================================================================
//                    Copyright 2013-2018 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________
//
//!     \file
//!     \brief Returns whether a string begins with another one.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_pjj1lvDnitxdxtZbFZ64jGnnUhPhHABq
#define BREATH_GUARD_pjj1lvDnitxdxtZbFZ64jGnnUhPhHABq

#include <string>

namespace breath {

//      [FUTURE] C++20 will have std::string::starts_with() for this.
//  ------------------------------------------------------------------------
bool                begins_with( std::string const & str,
                                 std::string const & with ) noexcept ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
