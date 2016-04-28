// =========================================================================
//                       Copyright 2007 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#ifndef BREATH_GUARD_ivBlyIgMoh0KJl1p5J44xFCWiI9nPqRi
#define BREATH_GUARD_ivBlyIgMoh0KJl1p5J44xFCWiI9nPqRi

/*
        An extension of container::size to cover both standard containers and
        built-in arrays.

        The syntax is, uniformly,

            breath::count( a )

        regardless of the actual type of a. See also
        begin_end.hpp.

        These functions are made obsolete in C++14 by the namespace scope
        std::size()'s. However our version uses, for containers, a
        conditional noexcept that the standard version doesn't have.
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
std::size_t constexpr
count( T const ( & )[ n ] ) noexcept
{
    return n ;
}

//      count:
//      ------
//
//      Same as t.size(), for any standard container.
// -----------------------------------------------------------------------
template< typename T >
typename T::size_type constexpr
count( T const & t ) noexcept( noexcept( t.size() ) )
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

