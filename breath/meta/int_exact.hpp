// =========================================================================
//                    Copyright 2006-2008 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#ifndef BREATH_GUARD_HdHZPdx1OyaeosOjcrni6ByNfUBalEG4
#define BREATH_GUARD_HdHZPdx1OyaeosOjcrni6ByNfUBalEG4

/*! \file   int_exact.hpp
    \brief
        A generic version of C99's exact-width integer types (intN_t).

        As for their C99 counterparts, there's no guarantee that they
        are provided for any given value of N.
*/

#include "breath/cpp11/long_long.hpp"
#include "breath/meta/select.hpp"
#include <limits>
#include <cstddef>

namespace breath {
namespace int_exact_private {

// FUTURE
// ------
//
//  This file could use <stdint.h> or <cstdint>
//  when they will be available. [gps]
// ---------------------------------------------------------
//
// This might be elegantly implemented via type lists or maps,
// but we chose to keep metaprogramming (and dependencies) to
// a minimum.
//
template< typename IntType, int index > struct types ;

// "list" of unsigned (list of signed not yet implemented [gps])
//
template<> struct types< unsigned, 0 > { typedef unsigned char    type ; } ;
template<> struct types< unsigned, 1 > { typedef unsigned short   type ; } ;
template<> struct types< unsigned, 2 > { typedef unsigned int     type ; } ;
template<> struct types< unsigned, 3 > { typedef unsigned long    type ; } ;
template<> struct types< unsigned, 4 > { typedef unsigned_long_long_type type ; } ;


template< std::size_t width,
          typename IntType,
          int n >
class selector
{
    typedef types< IntType, n > candidate ;
    enum { found =
        std::numeric_limits< typename candidate::type >::digits == width } ;

public:
    typedef typename meta::select_< found,
                                    candidate,
                                    selector< width, IntType, 1 + n >
                                  >::type s ;

    typedef typename s::type type ;
} ;

}


//!
//! \typereq
//!     \p T shall be either \c signed \c int or \c unsigned \c int
//!
template< std::size_t width, typename T /* gps temp = signed */ >
class int_exact
{
public:
    typedef typename int_exact_private
                         ::selector< width, T, 0 >::type type ;
} ;

//!
//! A convenience shortcut to int_exact< N, unsigned >
//!
template< std::size_t width >
class uint_exact
    : public int_exact< width, unsigned >
{
} ;


}


#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
