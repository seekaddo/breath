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
    //  This implementation uses GetPhysicallyInstalledSystemMemory(),
    //  if available, with a fallback to GlobalMemoryStatusEx().
    //  This is to make the function work pre Vista SP1. However
    //  only the first API gives an accurate value.
    // --------------------------------------------------------------
    HMODULE const       module = GetModuleHandleA( "kernel32" ) ;
    if ( module == NULL ) {
        throw last_api_error( "Cannot get a handle to kernel32.dll" ) ;
    }

    ULONGLONG           amount ;
    typedef BOOL ( WINAPI * fn_ptr_type )( ULONGLONG * ) ;
    fn_ptr_type const   get_physical_memory = reinterpret_cast< fn_ptr_type >(
             GetProcAddress( module, "GetPhysicallyInstalledSystemMemory" ) ) ;
    if ( get_physical_memory == nullptr
        || get_physical_memory( &amount ) == 0 ) {
        MEMORYSTATUSEX      status ;
        status.dwLength = sizeof status ;
        if ( GlobalMemoryStatusEx( &status ) == 0 ) {
            throw last_api_error( "GlobalMemoryStatusEx() failed" ) ;
        }
        return status.ullTotalPhys / 1024 ;
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
