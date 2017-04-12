// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/environment/node_id.hpp"
#include "breath/diagnostics/exception.hpp"
#include "breath/memory/auto_array.hpp"
#include <algorithm>
#include <Windows.h>
#include <Iphlpapi.h>

namespace breath {

node_id::node_id()
{
    //  The MSDN says:
    //      "On Windows XP and later: Use the GetAdaptersAddresses function
    //       instead of GetAdaptersInfo"
    //  but in my headers there's no declaration of GetAdaptersAddresses.
    //  ----------------------------------------------------------------------
    ULONG               size = 15 * 1024 ;
    auto_array< unsigned char >
                        array( new unsigned char[ size ] ) ;
    auto                info = reinterpret_cast< PIP_ADAPTER_INFO >( array.get() ) ;
    DWORD               r = ::GetAdaptersInfo( info, &size ) ;
    if ( r == ERROR_BUFFER_OVERFLOW ) {
        array.reset( new unsigned char[ size ] ) ;
        info = reinterpret_cast< PIP_ADAPTER_INFO >( array.get() ) ;
        r = ::GetAdaptersInfo( info, &size ) ;
    }

    if ( r != ERROR_SUCCESS ) {
        throw exception( "cannot get network adapters info" ) ;
    }
    bool                found = false ;
    while ( info != nullptr && ! found ) {
        if ( info->Type == MIB_IF_TYPE_ETHERNET
                && info->AddressLength == m_address.size() ) {

            found = true ;
            std::copy_n( &info->Address[ 0 ], m_address.size(), &m_address[ 0 ] ) ;
        }
        info = info->Next ;
    }

    if ( ! found ) {
        throw exception( "no suitable network adapter found" ) ;
    }
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
