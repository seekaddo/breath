// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/mathematics/next_multiple.hpp"
#include "breath/diagnostics/assert.hpp"

#include <cmath>

namespace breath {

std::intmax_t
next_multiple( std::intmax_t a, std::intmax_t b ) noexcept
{
    BREATH_ASSERT( b > 0 ) ;

    intmax_t const      abs_a = std::abs( a ) ;
    intmax_t const      r = abs_a % b ;
    return r == 0
        ? a
        : ( a < 0 )
            ? - ( abs_a - r )
            : a + b - r
        ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
