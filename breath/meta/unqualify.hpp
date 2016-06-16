// =========================================================================
//                       Copyright 2006 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#ifndef BREATH_GUARD_y2qhOILUvLqZ79ED32KSdlOabmhuefgQ
#define BREATH_GUARD_y2qhOILUvLqZ79ED32KSdlOabmhuefgQ

/*! \file   unqualify.hpp
    \brief
        Metafunction to get the corresponding unqualified type of
        its argument.

        Example: unqualify< char const >::type = char
*/

// NOTE:
//      No #includes here
//
//      This is a very basic facility, used by many other
//      components of the meta subsystem; do not introduce
//      dependencies (they are not logically necessary:
//      the C++ template system has all that is needed
//      to implement the functionality)

namespace breath {
namespace meta {

template< typename T >
class unqualify
{
public:
    typedef T type ;
} ;

template< typename T >
class unqualify< T const >
{
public:
    typedef T type ;
} ;

template< typename T >
class unqualify< T volatile >
{
public:
    typedef T type ;
} ;

template< typename T >
class unqualify< T volatile const >
{
public:
    typedef T type ;
} ;

}
}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
