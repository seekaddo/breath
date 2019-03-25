// =========================================================================
//                    Copyright 2016-2017 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/environment/node_id.hpp"
#include "breath/diagnostics/exception.hpp"
#include "breath/memory/auto_array.hpp"

#include <Winsock2.h>
#include <Iphlpapi.h>

#include <algorithm>

namespace breath {

node_id::node_id()
{
    ULONG               size = 15 * 1024 ;
    int                 attempts = 0 ;
    int const           max_attempts = 3 ;
    ULONG               r = 0 ;
    auto_array< unsigned char >
                        array ;
    IP_ADAPTER_ADDRESSES *
                        addresses = nullptr ;
    do {
        ++ attempts ;
        array.reset( new unsigned char[ size ] ) ;
        addresses = reinterpret_cast< IP_ADAPTER_ADDRESSES * >( array.get() ) ;
        r = GetAdaptersAddresses( AF_UNSPEC, 0, nullptr, addresses, &size ) ;
    } while ( r == ERROR_BUFFER_OVERFLOW && attempts <= max_attempts ) ;

    if ( r != ERROR_SUCCESS ) {
        throw exception( "node_id::node_id(): cannot get network adapters info" ) ;
    }
    bool                found = false ;
    while ( addresses != nullptr && ! found ) {
        if ( addresses->IfType == IF_TYPE_ETHERNET_CSMACD
                && addresses->PhysicalAddressLength == m_address.size() ) {

            found = true ;
            std::copy_n( &addresses->PhysicalAddress[ 0 ], m_address.size(),
                                                            &m_address[ 0 ] ) ;
        }
        addresses = addresses->Next ;
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
