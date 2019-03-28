// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/mathematics/gcd.hpp"
#include <cmath>

namespace breath {

template< typename M, typename N >
std::common_type_t< M, N > constexpr
lcm( M a, N b ) noexcept
{
    std::common_type_t< M, N > const
                        g = gcd( a, b ) ;
    return g == 0
        ? 0
        : std::abs( a ) / g * std::abs( b ) ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
