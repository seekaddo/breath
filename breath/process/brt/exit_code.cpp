// =========================================================================
//                       Copyright 2010 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/process/exit_code.hpp"
#include "breath/porting/dependent_code.hpp"
#include BREATH_DEPENDENT_CODE( system, exit_code.cpp )
#include <cstdlib>

namespace breath {

// These two can be specified portably, so we define them outside of the
// system-dependent exit_code.cpp's.
//
int const           exit_success( 0 ) ;
int const           exit_failure( EXIT_FAILURE ) ;

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
