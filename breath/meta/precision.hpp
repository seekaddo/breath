// =========================================================================
//                       Copyright 2006 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________
//
//!     \file
//!     \brief Metafunction yielding the \e precision of a type.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_crv8sfpsGwWru7Bdt9WKSehiAw6f4zgz
#define BREATH_GUARD_crv8sfpsGwWru7Bdt9WKSehiAw6f4zgz

/*!
    \todo document!

    The library provides specializations for all integer types and \e
    built-in arrays thereof (including multidimensional arrays).
    The user can specialize it for UDTs. See also \c width< T >. // gps
*/

#include "breath/meta/constant.hpp"

#include <cstddef>
#include <limits>

namespace breath {
namespace meta {

template< typename T >
class precision
    : public constant< T, std::numeric_limits< T >::digits >
{
} ;

template< typename T, std::size_t n >
class precision< T[ n ] >
    : public constant< std::size_t, n * precision< T >::value >
{
} ;

}
}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
