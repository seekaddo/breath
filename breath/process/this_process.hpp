// =========================================================================
//                       Copyright 2015 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________
//
//!     \file
//!     \brief Represents the process of the calling code.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_cTwXYy0xHxVtUgvI0o8Sme94ALCfx0R9
#define BREATH_GUARD_cTwXYy0xHxVtUgvI0o8Sme94ALCfx0R9

#include "breath/process/process.hpp"
#include <string>

namespace breath {

class this_process
    :   public process
{
public:

    //! Gets the current directory of the current process.
    // -----------------------------------------------------------------------
    static std::string  current_directory() ;

    //! Sets the current directory of the current process; 'dir' must be
    //! a valid directory path.
    // -----------------------------------------------------------------------
    static void         set_current_directory( std::string const & dir ) ;

    //! Waits for a process to exit.
    // -----------------------------------------------------------------------
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
