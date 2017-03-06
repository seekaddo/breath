// =========================================================================
//                       Copyright 2011 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________
//
//!     \file
//!     \brief Splits a \c std::string into a \c std::vector of strings.
// -------------------------------------------------------------------------

#include<string>
#include <vector>

namespace breath {

std::vector< std::string >
                    split( std::string const & s, char delim ) ;

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
