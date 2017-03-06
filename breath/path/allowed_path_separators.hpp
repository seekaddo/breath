// =========================================================================
//                    Copyright 2015-2017 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________
//
//!     \file
//!     \brief Returns the allowed path separators in the running system.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_bvA1h6sHG51DDAzrkOaJBHIxlZBpgVnA
#define BREATH_GUARD_bvA1h6sHG51DDAzrkOaJBHIxlZBpgVnA

namespace breath {

//!     Note that the separators are returned with the "preferred" one
//!     first.
//!
//!     Visual Studio fails to link if I declare this function as
//!     constexpr, so I avoid that for now.
// -------------------------------------------------------------------------
char const *        allowed_path_separators() noexcept ; //gps constexpr?

}
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
