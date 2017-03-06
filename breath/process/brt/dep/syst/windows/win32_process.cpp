// =========================================================================
//                       Copyright 2015 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/process/win32_process.hpp"
#include "breath/process/private/handle.hpp"
#include "breath/diagnostics/last_api_error.hpp"
#include <Windows.h>
#include <Psapi.h>

namespace breath {

std::string
win32_process::name() const
{
    process_private::handle const
                        h( OpenProcess(
                                PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
                                FALSE,
                                id()
                            ) ) ;
    if ( h.get() == NULL ) {
        throw last_api_error( "OpenProcess failed" ) ;
    }

    HMODULE             main_module ;
    DWORD               bytes_needed ;
    auto const          ret = EnumProcessModulesEx(
                                    h.get(),
                                    &main_module,
                                    sizeof main_module,
                                    &bytes_needed,
                                    LIST_MODULES_ALL
                                 ) ;
    if ( ret == 0 ) {
        throw last_api_error( "EnumProcessModulesEx failed" ) ;
    }

    char                process_name[ 1 + MAX_PATH ] ;
    if ( GetModuleBaseNameA( h.get(), main_module,
                            &process_name[ 0 ], sizeof process_name ) == 0 ) {
        throw last_api_error( "GetModuleBaseNameA failed" ) ;
    }

    return process_name ;
}

std::size_t
win32_process::module_count() const
{
    process_private::handle const
                        h( OpenProcess(
                                PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
                                FALSE,
                                id()
                            ) ) ;
    if ( h.get() == NULL ) {
        throw last_api_error( "OpenProcess failed" ) ;
    }

    HMODULE             dummy ;
    DWORD               bytes_needed ;
    auto const          ret = EnumProcessModulesEx(
                                    h.get(),
                                    &dummy,
                                    sizeof dummy,
                                    &bytes_needed,
                                    LIST_MODULES_ALL
                                 ) ;
    if ( ret == 0 ) {
        throw last_api_error( "EnumProcessModulesEx failed" ) ;
    }
    return bytes_needed / sizeof( HMODULE ) ;
}


}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
