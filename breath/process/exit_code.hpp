// =========================================================================
//                    Copyright 2006-2010 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________
//
//!     \file
//!     \brief Named constants for program termination codes.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_jUGeAMeGfcMWbQ12OyJckoIpy0CYCBq0
#define BREATH_GUARD_jUGeAMeGfcMWbQ12OyJckoIpy0CYCBq0

namespace breath {

extern int const    exit_success ;
extern int const    exit_failure ;

//      Maintenance note:
//
//      keep the in sync with *all* the .cpp files of the various code
//      variants (brt/dep/ subdirectory).
//   -----------------------------------------------------------------------
extern int const    exit_warning ;
extern int const    exit_error ;
extern int const    exit_fatal ;
extern int const    exit_internal ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
