// =========================================================================
//                       Copyright 2013 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________


// gps temp
#undef NDEBUG
#include <assert.h>
#define DO_TEST( cond ) assert( (cond) )

//----------------------

#include "breath/random/entropy_source.hpp"

int
main()
{
    breath::entropy_source
                        source ;

    source.release() ;

    // check that a second release doesn't yield "success"
    //
    DO_TEST( source.release() == false ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
