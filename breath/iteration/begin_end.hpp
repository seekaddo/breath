// =========================================================================
//                    Copyright 2006-2015 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________
//
//!     \file
//!     \brief Namespace-scope \c begin() and \c end().
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_Ve2uzZNiUDgCTZXgV1iB3bUD5U0n1kKD
#define BREATH_GUARD_Ve2uzZNiUDgCTZXgV1iB3bUD5U0n1kKD

/*!
        Syntax adaptors to extend the usage of begin() and end() to
        C-style arrays. Also defines cbegin() and cend(), with the
        same extent.

        All of the function templates are non-members, and the
        syntax is, uniformly
          <code>
            breath::begin( a ) ;
            breath::end( a ) ;
          </code>
        regardless of whether a refers to a standard container or
        to a built-in array. See also count.hpp.


    [C++0x], [Future]:
    C++11 should have a version of these, using the auto
    type-specifier and decltype().

    So perhaps my version will just go with time.

    Last checked in:

      n3242, 28 Feb. 2011 -- 24.6.5 [iterator.range]

    (there seems to be an editorial issue: 24.6 is about stream
    iterators, and 24.6.5 is a sub-paragraph of it.)

*/

#include <cstddef>

namespace breath {

//      begin:
//      ------
//
//!     Same as c.begin(), for any standard container.
// -----------------------------------------------------------------------
template< typename C >
typename C::iterator
begin( C & c ) noexcept( noexcept( c.begin() ) )
{
    return c.begin() ;
}

//      begin:
//      ------
//
//!     Same as c.begin(), for any standard container.
// -----------------------------------------------------------------------
template< typename C >
typename C::const_iterator
begin( C const & c ) noexcept( noexcept( c.begin() ) )
{
    return c.begin() ;
}

//      cbegin:
//      -------
//
//!     Same as c.begin(), for any standard container.
// -----------------------------------------------------------------------
template< typename C >
typename C::const_iterator
cbegin( C const & c ) noexcept( noexcept( c.begin() ) )
{
    return c.begin() ;
}


//      end:
//      ----
//
//!     Same as c.end(), for any standard container.
// -----------------------------------------------------------------------
template< typename C >
typename C::iterator
end( C & c ) noexcept( noexcept( c.end() ) )
{
    return c.end() ;
}

//      end:
//      ----
//
//!     Same as c.end(), for any standard container.
// -----------------------------------------------------------------------
template< typename C >
typename C::const_iterator
end( C const & c ) noexcept( noexcept( c.end() ) )
{
    return c.end() ;
}

//      cend:
//      -----
//
//!     Same as c.end(), for any standard container.
// -----------------------------------------------------------------------
template< typename C >
typename C::const_iterator
cend( C const & c ) noexcept( noexcept( c.end() ) )
{
    return c.end() ;
}

//      begin:
//      ------
//
//!     Like container::begin, but for a built-in array.
//!
//!     (Note that there's no need for a "T const overload")
// -----------------------------------------------------------------------
template< typename T, std::size_t n >
T *
begin( T ( &a )[ n ] ) noexcept
{
    return a ;
}

//      cbegin:
//      -------
//
//!     Like container::begin, but for a built-in array.
// -----------------------------------------------------------------------
template< typename T, std::size_t n >
T const *
cbegin( T const ( &a )[ n ] ) noexcept
{
    return a ;
}

//      end:
//      ----
//
//!     Like container::end, but for a built-in array.
//
//!     (The remark about begin() and overloading on const applies
//!     here as well)
// -----------------------------------------------------------------------
template< typename T, std::size_t n >
T *
end( T ( &a )[ n ] ) noexcept
{
    return a + n ;
}

//      cend:
//      -----
//
//!     Like container::end, but for a built-in array.
// -----------------------------------------------------------------------
template< typename T, std::size_t n >
T const *
cend( T const (&a)[ n ] ) noexcept
{
    return a + n ;
}

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
