// =========================================================================
//                       Copyright 2015 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________
//
//!     \file
//!     \brief Gets a map with all the environment variables and their
//!            values.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_U4BCWO9huCRrS51C9yYWQld0Ixzmwe5L
#define BREATH_GUARD_U4BCWO9huCRrS51C9yYWQld0Ixzmwe5L

#include <map>
#include <string>

namespace breath {

//! \return A map with all name-value pairs corresponding to the
//!         defined environment variables.
// -------------------------------------------------------------------------
std::map< std::string, std::string >
                    get_environment() ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
