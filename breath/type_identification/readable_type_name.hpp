// =========================================================================
//                    Copyright 2017-2018 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________
//
//!     \file
//!     \brief Returns a human readable name for its type parameter.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_e0aZnjL0UZmNVTa9XkUU1WypgFnHm24u
#define BREATH_GUARD_e0aZnjL0UZmNVTa9XkUU1WypgFnHm24u

#include <string>

namespace breath {

//!     \return A human readable name for the type \c T.
//!
//!     Limitations: if T is a reference to a possibly cv-qualified
//!     type, the name returned is that of the cv-unqualified
//!     referenced type; if T is a cv-qualified type, the name
//!     returned is that of the cv-unqualified type.
//!
//!     Furthermore,  if T is a class type or a reference to a class
//!     type, the class shall be completely-defined.
// -------------------------------------------------------------------------
template< typename T >
std::string         readable_type_name() ;

}

#include "brt/readable_type_name.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
