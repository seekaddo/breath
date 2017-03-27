// =========================================================================
//                    Copyright 2006-2015 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
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
    //!     A typedef for the type \c T.
    // ---------------------------------------------------------------------
    typedef T type;

    //!     A typedef for <code>select_< !condition, T, U ></code>.
    // ---------------------------------------------------------------------
    typedef select_< !condition, T, U > opposite;
} ;

template< typename T, typename U >
class select_< false, T, U >
{
public:
    //!     A typedef for the type \c U.
    // ---------------------------------------------------------------------
    typedef U type;

    //!     A typedef for <code>select_< true, T, U ></code>
    typedef select_< true, T, U > opposite;
} ;

//!     The truly polymorphic select template.
// -------------------------------------------------------------------------
template< typename Cond, typename T, typename U >
class select
{
public:
    //!     The result of the meta-function.
    // ---------------------------------------------------------------------
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
