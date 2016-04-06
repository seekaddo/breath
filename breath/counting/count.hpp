// =========================================================================
//                       Copyright 2007 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________


#ifndef BREEZE_COUNT_GPROTA_20070321_154859_HPP
#define BREEZE_COUNT_GPROTA_20070321_154859_HPP

/*
        An extension of container::size to cover both standard containers and
        built-in arrays.

        The syntax is, uniformly,

            breath::count( a )

        regardless of the actual type of a. See also
        begin_end.hpp.
*/

#include <cstddef>

namespace breath {

//      count:
//      ------
//
//      Returns the number of elements of the array argument
//      (obviously, n).
// -----------------------------------------------------------------------
template< typename T, std::size_t n >
std::size_t
count( T const ( & )[ n ] )
{
    return n ;
}

//      count:
//      ------
//
//      Same as t.size(), for any standard container.
// -----------------------------------------------------------------------
template< typename T >
typename T::size_type
count( T const & t ) // gps size_type??
{
    return t.size() ;
}

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:

