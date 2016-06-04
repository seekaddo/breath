// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

namespace breath {

template< typename T >
constexpr T const &
clamp( T const & value, T const & low, T const & high )
{
    return clamp( value, low, high, std::less<>() ) ;
}

template < typename T, typename Compare >
constexpr T const &
clamp( T const & value,
       T const & low,
       T const & high,
       Compare comp )
{
    //      NOTE: no BREATH_ASSERT( !comp( high, low ) ) here to avoid
    //            altering the stated complexity of the function (at most
    //            two applications of comp).
    // -----------------------------------------------------------------------
    return comp( value, low )
            ? low
            : comp( high, value )
                ? high
                : value
            ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
