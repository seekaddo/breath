// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include <algorithm>

namespace breath {

template< typename M, typename N >
std::common_type_t< M, N > //constexpr
gcd( M m, N n ) noexcept
{
    static_assert( std::is_integral< M >::value
                && std::is_integral< N >::value, "M && N must be integral" ) ;

    m = std::abs( m ) ;
    n = std::abs( n ) ;
    while ( true ) {

        if ( m == 0 ) {
            return n ;
        }
        n %= m ;

        if ( n == 0 ) {
            return m ;
        }
        m %= n ;
    }
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
