// =========================================================================
//                       Copyright 2006 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
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
    The user can specialize it for UDTs. See also width< T >. // gps
*/

#include "breath/meta/constant.hpp"

#include <cstddef>
#include <limits>

namespace breath {
namespace meta {

template< typename T >
class precision
#if 0
    : public successor< highest_bit_index< max< T > > >
#else
    : public constant< T, std::numeric_limits< T >::digits >
#endif
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
