// ===========================================================================
//                     Copyright 2006-2011 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// ___________________________________________________________________________

#ifndef BREATH_GUARD_AIxamIWyjxqb3pPGHU23CYP8v7Zo1TTt
#define BREATH_GUARD_AIxamIWyjxqb3pPGHU23CYP8v7Zo1TTt

//      accumulate():
//      =============
//
//      A generalized version of std::accumulate().
//
//      Traits
//      ------
//
//      breath::accumulate() uses accumulate_traits<> as a point of
//      customization: see below.
//
//      The default traits template performs a summation of the
//      elements in the range [begin, end) via operator+= (which is
//      searched via ADL).
//
//      Any accumulate_traits<> shall provide the following accessible
//      members:
//
//          - init_type
//          - result_type
//          - first()
//          - compute()
// ---------------------------------------------------------------------------

namespace breath {

//      accumulate_traits<>:
//      --------------------
//
//      Traits template for breath::accumulate<>().
//      (gps should we use the term "policy" in place of "traits"?)
// ---------------------------------------------------------------------------
template< typename T >
class accumulate_traits
{
public:
    typedef T           init_type ;
    typedef T           result_type ;

    static init_type    first() ;

    template< typename It >
    static result_type  compute( It begin, It end, init_type & value ) ;
} ;

//      accumulate():
//      -------------
//
//      Generalized version of std::accumulate().
//
//      breath::accumulate_traits<> is a customization point: you are
//      allowed to specialize it, in namespace breath, for your own
//      types.
// ---------------------------------------------------------------------------
template< typename InputIterator, typename T >
typename accumulate_traits< T >::result_type
accumulate( InputIterator begin,
            InputIterator end,
            T v = accumulate_traits< T >::first() ) ;

}

#include "brt/accumulate.tpp"
#endif
// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
