// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2010 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/process/exit_code.hpp"
#include "breath/porting/dependent_code.hpp"
#include BREATH_DEPENDENT_CODE( system, exit_code.cpp )
#include <cstdlib>

namespace breath_ns {

//      These two can be specified portably, so we define them outside
//      of the system-dependent exit_code.cpp's.
// ---------------------------------------------------------------------------
int const           exit_success = 0 ;
int const           exit_failure = EXIT_FAILURE ;

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
