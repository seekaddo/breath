// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include <type_traits>
#include <limits>

namespace breath {
namespace meta {

template< typename T >
constexpr bool
is_twos_complement() noexcept
{
    static_assert( std::is_integral< T >::value, "T must be an integral type" ) ;

    return ( std::numeric_limits< T >::min() + std::numeric_limits< T >::max() )
        == -1 ;
}

}
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
