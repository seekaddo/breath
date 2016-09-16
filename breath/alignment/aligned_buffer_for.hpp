// =========================================================================
//                       Copyright 2008 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#ifndef BREATH_GUARD_ilYRG2ibsfCoQd4vz7X5Cik5Q8E0z1pO
#define BREATH_GUARD_ilYRG2ibsfCoQd4vz7X5Cik5Q8E0z1pO

#include "breath/idiom/declare_non_copyable.hpp"
#include "breath/meta/select.hpp"
#include <cstddef>

namespace breath {


template< typename T >
class               aligned_buffer_for ;

template< typename T, std::size_t n >
class               aligned_buffer_for< T[ n ] > { /* disabled for arrays */ } ;


namespace aligned_buffer_private {


template< typename T >
class align_of
{
    struct hack
    {
        char                c ;
        T                   t ;
    } ;

public:
    static std::size_t const
                        value = sizeof( hack ) - sizeof( T ) ;
} ;

template< typename T >
std::size_t const       align_of< T >::value ;


template< std::size_t index >
struct              pod_array ;

static int const    number_of_pod_types = 7 ;

template<> struct   pod_array< 0 > { typedef char        type ; } ;
template<> struct   pod_array< 1 > { typedef short       type ; } ;
template<> struct   pod_array< 2 > { typedef int         type ; } ;
template<> struct   pod_array< 3 > { typedef long        type ; } ;
template<> struct   pod_array< 4 > { typedef float       type ; } ;
template<> struct   pod_array< 5 > { typedef double      type ; } ;
template<> struct   pod_array< 6 > { typedef long double type ; } ;
template<> struct   pod_array< number_of_pod_types > {
                // if you get to instantiate this you'll have to add
                // more types to the array
} ;


template< typename T, int start_index >
class searcher
{
    typedef         typename pod_array< start_index >::type
                        candidate ;
public:
    typedef typename meta::select_<
        align_of< candidate >::value == align_of< T >::value,
        candidate,
        searcher< T, start_index + 1 >
    >::type
                        type ;
} ;

template< typename T >
struct pod_with_same_align
{
    typedef typename searcher< T, 0 >::type
                        type ;
} ;


}

//      aligned_buffer_for
//      ==================
//
//!     A byte buffer suitably sized and aligned for the type \c T.
//!
//!     Note that this has a different interface from TR1's or C++11's
//!     analogous: both of the latter take one or two numeric arguments
//!     (size and alignment); this one takes just a type (the type that
//!     we want the same alignment of). Among other things, the C++11
//!     scheme allows for storing arrays:
//!
//!       aligned_storage< n * sizeof( T ), alignof( T ) >
//!
//!     What's more, C++11 has support for declaring an aligned buffer
//!     directly in core language:
//!
//!        alignas( T ) unsigned char arr[ sizeof( T ) ] ;
//!
//!     So: this facility exists basically for C++03; and all of the
//!     alternatives (this one, TR1's one and the library-based C++11's
//!     one) will be made superflous by C++11's core support.
// ---------------------------------------------------------------------
template< typename T >
class aligned_buffer_for
{
public:
    BREATH_DECLARE_NON_COPYABLE( aligned_buffer_for )

    aligned_buffer_for() {}

private:
    union
    {
        unsigned char   m_raw_buffer[ sizeof( T ) ] ;
        typename aligned_buffer_private::pod_with_same_align< T >::type
                        dummy_for_alignment ;
    } ;

public:
        void *          address()       { return m_raw_buffer ; }
        void const *    address() const { return m_raw_buffer ; }

} ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
