// =========================================================================
//                       Copyright 2015 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/diagnostics/assert.hpp"
#include "breath/diagnostics/last_api_error.hpp"
#include "breath/process/exit_code.hpp"
#include "breath/process/private/handle.hpp"

#include <vector>
#include <windows.h>

namespace breath {

class process::impl
{
public:
                        impl() : m_info()
                        {}
                        ~impl()
                        {
                            CloseHandle( m_info.hThread ) ;
                            CloseHandle( m_info.hProcess ) ;
                        }

    PROCESS_INFORMATION m_info ;
} ;

process::process()
    :   m_impl( new impl )
{
}

process::~process()
{
    delete m_impl ;
}

process::id_type
process::id() const
{
    return m_impl->m_info.dwProcessId ;
}

void
process::start( std::string const & app_name,
                std::string const & arguments,
                maybe<std::size_t> timeout_in_ms )
{
    std::vector< char > args( arguments.begin(), arguments.end() ) ;
    args.resize( args.size() + 1 ) ;

    STARTUPINFOA        si = { sizeof si };
    DWORD               creation_flags = ( GetConsoleWindow()
                                              ? 0
                                              : CREATE_NO_WINDOW ) ;
    
    int const           ret = CreateProcessA(
                                app_name.c_str(),
                                &args[ 0 ],
                                NULL,
                                NULL,
                                FALSE,
                                creation_flags,
                                NULL,
                                NULL,
                                &si,
                                &m_impl->m_info
                                ) ;
    if( ret == 0 ) {
        throw last_api_error( "CreateProcessA failed" ) ;
    }

    if ( timeout_in_ms.is_valid() ) {
        BREATH_ASSERT( timeout_in_ms.value() > 0 ) ;
        if( WaitForSingleObject( m_impl->m_info.hProcess, timeout_in_ms.value() ) ==
                                                                WAIT_FAILED ) {
            throw last_api_error( "WaitForSingleObject failed" ) ;
        }
        try {
            terminate() ;
        } catch( ... ) {
        }
    }
    //CloseHandle( pi.hThread ) ;
    //CloseHandle( pi.hProcess ) ;
}

void
process::kill()
{
    HANDLE const        h = OpenProcess( PROCESS_TERMINATE, false, m_impl->m_info.dwProcessId ) ;
    if ( h == NULL ) {
        throw last_api_error( "OpenProcess failed" ) ;
    }
    if ( TerminateProcess( h, exit_failure ) == 0 ) {
        CloseHandle( h ) ;
        throw last_api_error( "TerminateProcess failed" ) ;
    }
    if ( CloseHandle( h ) == 0 ) {
        throw last_api_error( "CloseHandle failed" ) ;
    }
}

void
process::terminate()
{
    DWORD               exit_code ;
    if ( GetExitCodeProcess( m_impl->m_info.hProcess, &exit_code) == 0 ) {
        throw last_api_error( "GetExitCodeProcess failed" ) ;
    }
    if ( exit_code == STILL_ACTIVE ) {
        FARPROC             exit_proc = GetProcAddress(
                             GetModuleHandleA("kernel32.dll"), "ExitProcess" ) ;

        unsigned            dummy = 0 ;
        process_private::handle const
                            h( CreateRemoteThread(
                                    m_impl->m_info.hProcess, NULL, 0,
                                     reinterpret_cast< LPTHREAD_START_ROUTINE >(
                                                                     exit_proc),
                                     &dummy, 0, NULL ) ) ;
        if ( h.get() == NULL ) {
            throw last_api_error( "CreateRemoteThread failed" ) ;
        }
    }
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
