// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________
//
//!     \file
//!     \brief The least common multiple of two integers.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_OFEP2tStNzXnzGYEV6JdW1XUXcS6lA7p
#define BREATH_GUARD_OFEP2tStNzXnzGYEV6JdW1XUXcS6lA7p

#include <type_traits>

namespace breath {

//!     This function follows the C++ Library Fundamental TS v2, as of
//!     May 14, 2016. (It adds, as allowed, a noexcept specification.)
//!
//!     If either \c M or \c N is not an integral type the program is
//!     ill-formed. If |m| is not representable as a value of type M
//!     or |n| is not representable as a value of type N or the least
//!     common multiple of |m| and |n| is not representable as a value
//!     of type \c common_type_t< M, N>, the behavior is undefined.
//!
//!     \returns
//!     If either \c m or \c n is zero, returns zero. Otherwise it
//!     returns the least common multiple of |m| and |n|.
// -------------------------------------------------------------------------
template< typename M, typename N >
constexpr std::common_type_t< M, N >
                    lcm( M m, N n ) noexcept ;


}

#include "brt/lcm.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
