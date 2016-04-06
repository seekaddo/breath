//////////////////////////////////////////////////////////////////////////////
//                   Copyright (c) 2006-2010 Gennaro Prota
//
//                 Licensed under the Simplified BSD License.
//            (See accompanying file SIMPLIFIED_BSD_LICENSE.txt or
//              <http://opensource.org/licenses/bsd-license.php>)//gps
//  _________________________________________________________________________

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
