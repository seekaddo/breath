// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________
//
//!     \file
//!     \brief Tells if an integer is a power of two.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_33316YlRoQ2LToi0iu44YByR2XFvlCOy
#define BREATH_GUARD_33316YlRoQ2LToi0iu44YByR2XFvlCOy

#include <limits>
#include <type_traits>

namespace breath {

//!     \return \c true if an only if \c x is a power of two.
// -------------------------------------------------------------------------
template< typename T >
constexpr typename std::enable_if< ! std::numeric_limits< T >::is_signed,
                                   bool >::type
                    is_power_of_two( T x ) noexcept ;

}

#include "brt/is_power_of_two.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
