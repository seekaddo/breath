// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________
//
//!     \file
//!     \brief A \c std::string trimmer.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_rws4wbvfhp1gTSnTPzZEhVe9JHM0Cwgk
#define BREATH_GUARD_rws4wbvfhp1gTSnTPzZEhVe9JHM0Cwgk

#include <string>

namespace breath {

class               set_of_chars ;

std::string         trim( std::string const & str ) ;

std::string         trim( std::string const &  str,
                          set_of_chars const & to_remove ) ;

}



#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
