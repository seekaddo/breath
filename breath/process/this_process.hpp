// =========================================================================
//                       Copyright 2015 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________
//
//!     \file
//!     \brief Represents the process of the calling code.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_cTwXYy0xHxVtUgvI0o8Sme94ALCfx0R9
#define BREATH_GUARD_cTwXYy0xHxVtUgvI0o8Sme94ALCfx0R9

#include "breath/idiom/declare_non_copyable.hpp"
#include "breath/process/process.hpp"
#include <string>

namespace breath {

class this_process
    :   public process
{
private:
                        this_process() ;

public:
    BREATH_DECLARE_NON_COPYABLE( this_process )

    this_process &      instance() ;


    //!     Gets the current directory of the current process.
    // ---------------------------------------------------------------------
    static std::string  current_directory() ;

    //!     Sets the current directory of the current process; 'dir'
    //!     must be a valid directory path.
    // ---------------------------------------------------------------------
    static void         set_current_directory( std::string const & dir ) ;

    //!     Waits for a process to exit.
    // ---------------------------------------------------------------------
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
