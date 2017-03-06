// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________
//
//!     \file
//!     \brief Tells whether a type uses a two's complement representation.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_tWPolV5CdSeUDR2dhiin3jIbwnOhvgwW
#define BREATH_GUARD_tWPolV5CdSeUDR2dhiin3jIbwnOhvgwW

namespace breath {
namespace meta {

//!     If \c T is not an integral type, the program is ill-formed.
//!     Otherwise \c is_twos_complement() returns true if and only if
//!     the type \c T uses a two's complement representation.
// -------------------------------------------------------------------------
template< typename T >
constexpr bool      is_twos_complement() noexcept ;

}
}

#include "brt/is_twos_complement.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
