// =========================================================================
//                    Copyright 2006-2010 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/diagnostics/assert.hpp"

#include <cstdlib>
#include <iostream>
#include <ostream>

namespace breath {
namespace assert_private {

//      Sends a message to std:cerr and aborts.
// -----------------------------------------------------------------------
void
fire( char const * message, char const * file_name, unsigned long line_number )
{
    std::cerr << "Assertion failed: "
              << message
              << ", file " << file_name
              << ", line " << line_number
              << std::endl ;

    std::abort() ;
}

}
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
