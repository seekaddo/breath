// =========================================================================
//                       Copyright 2011 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________
//
//!     \file
//!     \brief Converts an object to its textual representation.
// -------------------------------------------------------------------------

#include <string>

namespace breath {

template< typename OutputStreamable >
std::string         to_string( OutputStreamable const & ) ;

}

#include "brt/to_string.tpp"

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
