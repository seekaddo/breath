// =========================================================================
//                       Copyright 2015 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/diagnostics/last_api_error.hpp"
#include "breath/diagnostics/assert.hpp"
#include <Windows.h>
#include <cstddef>

namespace breath {

std::string
this_process::current_directory()
{
    DWORD const         required = GetCurrentDirectoryA( 0, nullptr ) ;
    if ( required == 0 ) {
        throw last_api_error( "GetCurrentDirectoryA( 0, nullptr ) failed" ) ;
    }
    // assumes contiguity of std::string, as required by C++11
    std::string         s( required, '\0' ) ;
    if ( GetCurrentDirectoryA( required, &s[ 0 ] ) == 0 ) {
        throw last_api_error( "GetCurrentDirectoryA failed" ) ;
    }
    s.resize( s.size() - 1 ) ; // remove trailing '\0'
    return s;
}

void
this_process::set_current_directory( std::string const & dir )
{
    BREATH_ASSERT( 0 < dir.length() && dir.length()  < MAX_PATH ) ;
    BREATH_ASSERT( dir.back() =='\\' || dir.length() <= (MAX_PATH-2) ) ;
    if( SetCurrentDirectoryA( dir.c_str() ) == 0 ) {
        throw last_api_error( "SetCurrentDirectoryA failed" ) ;
    }
}

void
this_process::wait( process const & pr )
{
    HANDLE const        h = OpenProcess(
                PROCESS_QUERY_INFORMATION | SYNCHRONIZE, FALSE, pr.id() ) ;
    if( h == NULL ) {
        throw last_api_error( "OpenProcess failed" ) ;
    }
    if ( WaitForSingleObject( h, INFINITE ) == WAIT_FAILED ) {
        CloseHandle( h ) ;
        throw last_api_error( "WaitForSingleObject failed" ) ;
    }
    if ( CloseHandle( h ) == 0 ) {
        throw last_api_error( "CloseHandle failed" ) ;
    }
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
