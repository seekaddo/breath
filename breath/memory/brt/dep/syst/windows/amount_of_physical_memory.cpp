// =========================================================================
//                       Copyright 2017 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/memory/amount_of_physical_memory.hpp"
#include "breath/diagnostics/last_api_error.hpp"

#include <Windows.h>

namespace breath {

unsigned long long
amount_of_physical_memory()
{
    ULONGLONG           amount ;
    if ( GetPhysicallyInstalledSystemMemory( &amount ) == 0 ) {
        throw last_api_error( "GetPhysicallyInstalledSystemMemory() failed" ) ;
    }
    return amount ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
