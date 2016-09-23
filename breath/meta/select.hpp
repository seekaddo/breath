// =========================================================================
//                    Copyright 2006-2015 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________
//
//!     \file
//!     \brief Compile-time selection between types.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_Mcff5zkaJE9eTbXnwJQWQ2WlCXIXfcmc
#define BREATH_GUARD_Mcff5zkaJE9eTbXnwJQWQ2WlCXIXfcmc

namespace breath {
namespace meta {

template< bool condition, typename T, typename U >
class select_
{
public:
    typedef T type;
    typedef select_< !condition, T, U > opposite;
} ;

template< typename T, typename U >
class select_< false, T, U >
{
public:
    typedef U type;
    typedef select_< true, T, U > opposite;
} ;

template< typename Cond, typename T, typename U >
class select
{
public:
    typedef typename select_< Cond::value, T, U >::type type;
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
