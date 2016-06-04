// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include <iterator>

namespace breath {

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

template< typename InputIterator, typename OutputIterator, typename Compare >
OutputIterator clamp_range( InputIterator first,
                            InputIterator last,
                            OutputIterator result,
        typename std::iterator_traits< InputIterator >::value_type const & low,
        typename std::iterator_traits< InputIterator >::value_type const & high,
        Compare comp )
{
    using value_type = decltype( low ) ;
    return std::transform( first, last, result, [ & ]( value_type val )
                                 { return clamp( val, low, high, comp ) ; } ) ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
