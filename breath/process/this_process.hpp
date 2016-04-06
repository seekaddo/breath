// =========================================================================
//                       Copyright 2015 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#ifndef BREATH_GUARD_cTwXYy0xHxVtUgvI0o8Sme94ALCfx0R9
#define BREATH_GUARD_cTwXYy0xHxVtUgvI0o8Sme94ALCfx0R9

#include "breath/process/process.hpp"
#include <string>

namespace breath {

class this_process
    :   public process
{
public:

    static std::string  current_directory() ;
    static void         set_current_directory( std::string const & ) ;

    void                wait( process const & ) ;
} ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
