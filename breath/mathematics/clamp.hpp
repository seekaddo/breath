// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________
//
//  An implementation of the proposed clamp() templates.
//  See <http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2015/n4536.html>.
// --------------------------------------------------------------------------

#ifndef BREATH_GUARD_iVIpJl3Xhjhnj23ACP0NU6ffWo7q8kd4
#define BREATH_GUARD_iVIpJl3Xhjhnj23ACP0NU6ffWo7q8kd4

#include <algorithm>

namespace breath {

//      clamp():
//      ========
//
//!     Requires:
//!      1. T is LessThanComparable
//!      2. comp( high, low ) == false
//!     Returns:
//!         \c low if value is less than \c low, \c high if \c value is higher
//!         than \high, otherwise \c value
//!     Complexity:
//!         One or two applications of the Compare predicate.
//!     Remarks:
//!         Returns a reference to \c value when \c value is equivalent to
//!         one of the boundary arguments.
// --------------------------------------------------------------------------
template < typename T, typename Compare = std::less<> >
constexpr T const & clamp( T const & value,
                           T const & low,
                           T const & high,
                           Compare comp = Compare() ) ;

//      clamp_range():
//      ==============
//
//!     Requires:
//!      1. iterator_traits< InputIterator >::value_type is LessThanComparable
//!         and CopyAssignable
//!      2. comp( high, low ) == false
//!     Returns:
//!         result + ( last - first )
//!     Complexity:
//!         Exactly last-first applications of \c clamp() with the corresponding
//!         predicate
//!     Remarks:
//!         \c result may be equal to \c first
// --------------------------------------------------------------------------
template< typename InputIterator, typename OutputIterator,
          typename Compare = std::less<> >
OutputIterator clamp_range( InputIterator first,
                            InputIterator last,
                            OutputIterator result,
           typename std::iterator_traits< InputIterator >::value_type const& low,
           typename std::iterator_traits< InputIterator >::value_type const& high,
           Compare comp = Compare() ) ;

}

#include "brt/clamp.tpp"
#endif
// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
