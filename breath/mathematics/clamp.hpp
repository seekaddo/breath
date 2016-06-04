// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________
//
//  An implementation of the proposed clamp() templates.
//  See <http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2015/n4536.html>,
//    <http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2015/p0025r1.html>
//  and
//    <http://www.open-std.org/jtc1/sc22/wg21/docs/lwg-active.html#2688>.
// --------------------------------------------------------------------------

#ifndef BREATH_GUARD_iVIpJl3Xhjhnj23ACP0NU6ffWo7q8kd4
#define BREATH_GUARD_iVIpJl3Xhjhnj23ACP0NU6ffWo7q8kd4

#include <algorithm>

namespace breath {

//      clamp():
//      ========
//
//!     Requires:
//!      1. T shall be LessThanComparable
//!      2. high shall be no lower than low
//!     Returns:
//!         \c low if value is less than \c low, \c high if \c value is higher
//!         than \high, otherwise \c value
//!     Complexity:
//!         One or two comparisons.
//!     Remarks:
//!         The function template returns a reference to \c value when \c value
//!         is equivalent to one (or both) of the boundary arguments.
// --------------------------------------------------------------------------
template< typename T >
constexpr T const & clamp( T const & value, T const & low, T const & high ) ;

//      clamp():
//      ========
//
//!     Requires:
//!         comp( high, low ) == false
//!     Returns:
//!         \c low if value is less than \c low, \c high if \c value is higher
//!         than \high, otherwise \c value
//!     Complexity:
//!         One or two comparisons.
//!     Remarks:
//!         The function template returns a reference to \c value when \c value
//!         is equivalent to one (or both) of the boundary arguments.
// --------------------------------------------------------------------------
template < typename T, typename Compare  >
constexpr T const & clamp( T const & value,
                           T const & low,
                           T const & high,
                           Compare comp ) ;

}

#include "brt/clamp.tpp"
#endif
// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
