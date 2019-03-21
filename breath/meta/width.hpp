// =========================================================================
//                       Copyright 2006 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________
//
//!     \file
//!     \brief Metafunction yielding the \e width of a type.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_KvNAPbTCTNbIqTMjUCtxwBFR3ipIdp2y
#define BREATH_GUARD_KvNAPbTCTNbIqTMjUCtxwBFR3ipIdp2y

#include "breath/meta/constant.hpp"
#include "breath/meta/has_sign.hpp"
#include "breath/meta/precision.hpp"
#include "breath/meta/select.hpp"
#include "breath/meta/successor.hpp"

#include <cstddef>

namespace breath {
namespace meta {

//      width:
//      ======
//
//!     A \c meta::constant whose \c value_type is \p T and whose value
//!     is the \c width of \p T (the number of bits it uses to
//!     represent values, including any sign but excluding any padding
//!     bits).
//!
//!     \par Type requirements
//!         See \c meta::precision.
// -------------------------------------------------------------------------
template< typename T >
class width
    : public select< has_sign< T >,
                     successor< precision < T > >,
                     precision < T >
                   >::type
{
} ;

template< typename T, std::size_t n >
class width< T[ n ] >
    : public constant< std::size_t, n * width< T >::value >
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
