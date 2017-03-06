// =========================================================================
//                    Copyright 2006-2007 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________
//
//!     \file
//!     \brief  SHA functions common code.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_YZVt6T2boY9RlFkqeiYohH0bEc6w6tsM
#define BREATH_GUARD_YZVt6T2boY9RlFkqeiYohH0bEc6w6tsM

#include <limits>

namespace breath {
namespace sha_common_private {


//      the "choice" function - for each bit position p it acts as a
//      conditional: "if x(p) then y(p) else z(p)"
// -------------------------------------------------------------------------
template< typename T >
T
ch( T x, T y, T z )
{
    return ( x & y ) | ( ~x & z ) ;
}

//      "majority" function - for each bit position the result is 1 if
//      and only if at least two of the three bits are 1
// -------------------------------------------------------------------------
template< typename T >
T
maj( T x, T y, T z )
{
    return ( x & y ) | ( x & z ) | ( y & z ) ;
}

//      rotate right - usual constraints on amount apply
// -------------------------------------------------------------------------
template< int amount, typename T >
T
ror( T x )
{
    return ( x >> amount )
         | ( x << ( std::numeric_limits< T >::digits - amount ) ) ;
}


}}


#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:

