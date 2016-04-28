// =========================================================================
//                    Copyright 2011-2013 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________


#include "breath/random/subrange_max.hpp"
#include "breath/diagnostics/assert.hpp"


//      Implementation:
//      ---------------
//
//      We want to have a range [0, p] such as p+1 (the number of
//      values that it contains) is a multiple of x+1 (the number of
//      values in [0, x]).
//
//      Mathematically:
//
//         m+1 = q(x+1) + r
//
//      but *programmatically* we can't do that directly, because m+1
//      may overflow. However, substracting x+1 from both members
//      (which is fine....)
//
//         m-x = (q-1)(x+1) + r
//
//      which says that we can obtain the same remainder r performing
//      a division of m-x (which is non-negative) by x+1. Hence the
//      implementation below.
// ---------------------------------------------------------------------------
namespace breath {

unsigned long
subrange_max( unsigned long x, unsigned long m )
{
    BREATH_ASSERT( x <= m ) ;

    // note how x+1 cannot overflow in its branch (because,
    // there, x < m, and m has the same type as x)
    return x == m
        ? m
        : m - ( (m-x) % (x+1) )
        ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
