// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/diagnostics/assert.hpp"
#include "breath/meta/is_twos_complement.hpp"
#include <cmath>
#include <limits>

namespace breath {

template< typename M, typename N >
std::common_type_t< M, N > constexpr
gcd( M a, N b ) noexcept
{
    static_assert( std::is_integral< M >::value
                && std::is_integral< N >::value, "M && N must be integral" ) ;

    BREATH_ASSERT( ( !meta::is_twos_complement< M >()
        || a != std::numeric_limits< M >::min() )
        &&         ( !meta::is_twos_complement< N >()
        || b != std::numeric_limits< N >::min() ) ) ;

    a = std::abs( a ) ;
    b = std::abs( b ) ;
    while ( true ) {

        if ( a == 0 ) {
            return b ;
        }
        b %= a ;

        if ( b == 0 ) {
            return a ;
        }
        a %= b ;
    }
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
