// ===========================================================================
//                        Copyright 2018 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Digital root of a (non-negative) integer.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_XtTcG5ymuoVaWgnKITP3OQP7ggHKE44e
#define BREATH_GUARD_XtTcG5ymuoVaWgnKITP3OQP7ggHKE44e

#include "breath/top_level_namespace.hpp"

namespace breath_ns {

//      digital_root():
//      ===============
//
//!     \return
//!         The digital root of the number \c n in base \c base.
//!
//!     \pre
//!         n >= 0 && base >= 2
// ---------------------------------------------------------------------------
template< typename T >
constexpr int       digital_root( T n, int base = 10 ) noexcept ;

}

#include "brt/digital_root.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
