// =========================================================================
//                       Copyright 2011 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________
//
//!     \file
//!     \brief A \c std::string trimmer (head of string).
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_VJhjD7vyKemLfcukUGXm4RzXGSsdvmrL
#define BREATH_GUARD_VJhjD7vyKemLfcukUGXm4RzXGSsdvmrL

#include <string>

namespace breath {

class               set_of_chars ;
// gps dovrebbe rimuovere gli space secondo il locale?
std::string         trim_head( std::string const & str ) ;

std::string         trim_head( std::string const &  str,
                               set_of_chars const & to_remove ) ;
}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
