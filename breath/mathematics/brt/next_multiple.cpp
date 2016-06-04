// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/mathematics/next_multiple.hpp"
#include "breath/diagnostics/assert.hpp"

#include <limits>

namespace breath {

std::intmax_t
next_multiple( std::intmax_t a, std::intmax_t b ) noexcept
{
    BREATH_ASSERT( a <= (std::numeric_limits< std::intmax_t >::max() - b) ) ;
    return ( a/b + 1 ) * b ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
