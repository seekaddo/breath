// =========================================================================
//                    Copyright 2011-2019 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________
//
//!     \file
//!     \brief Splits a \c std::string into a \c std::vector of strings.
// -------------------------------------------------------------------------

#include <string>
#include <vector>

namespace breath {

//      split():
//      ========
//
//!     \return
//!         A vector of strings obtained by splitting \c s at each
//!         delimiter character \c delim, in order.
//!
//!     \note
//!         This should probably use \c set_of_chars.
// -------------------------------------------------------------------------
std::vector< std::string >
                    split( std::string const & s,
                           std::string const & delimiters ) ;

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
