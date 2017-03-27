// =========================================================================
//                       Copyright 2013 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/preprocessing/prevent_macro_expansion.hpp"

#define foo( a )    unexisting_function

void
(foo)( int )
{
}

int
main()
{
    foo BREATH_PREVENT_MACRO_EXPANSION ( 1 ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
