// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

namespace breath {

template< typename T >
constexpr typename std::enable_if< std::numeric_limits< T >::is_integer &&
                                   ! std::numeric_limits< T >::is_signed,
                                   bool >::type
                    is_power_of_two( T x ) noexcept
{
    return ( x & ( x-1 ) ) == 0 && x > 0 ;
}

//!     This specialization is logically unnecessary but silences MSVC
//!     warnings. Anyway, consider it experimental: it's possible that
//!     I'll add a static_assert( ! is_bool< T >::value ) ; to the
//!     primary template.
// -------------------------------------------------------------------------
template<>
inline constexpr bool
is_power_of_two< bool >( bool b ) noexcept
{
    return b ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
