// =========================================================================
//                       Copyright 2017 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/environment/node_id.hpp"
#include "breath/counting/count.hpp"
#include "breath/diagnostics/exception.hpp"

#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <algorithm>
#include <cstring>

namespace breath {

node_id::node_id()
{
    int const           failure = -1 ;
    int const           sock = socket( AF_INET, SOCK_DGRAM, IPPROTO_IP ) ;

    if ( sock == failure ) {
        throw exception( "could not create a socket" ) ;
    }

    const int           len = 4 * 1024 ;
    char                buffer[ len ] ;
    ifconf              ifc ;
    ifc.ifc_len = len ;
    ifc.ifc_buf = &buffer[ 0 ] ;

    if ( ioctl( sock, static_cast< int >( SIOCGIFCONF ), &ifc ) == failure ) {
        throw exception( "ioctl failed" );
    }

    ifreq const *       it = ifc.ifc_req ;
    ifreq const * const end = it + ( ifc.ifc_len / sizeof( ifreq ) ) ;
    bool                found = false ;
    while ( it != end && ! found ) {
        ifreq               ifr ;
        std::strcpy( ifr.ifr_name, it->ifr_name );
        if ( ioctl( sock, static_cast< int >( SIOCGIFFLAGS ), &ifr )
                                                                != failure ) {
            if ( ( ifr.ifr_flags & IFF_LOOPBACK ) == 0 ) {
                if ( ioctl( sock, static_cast< int >( SIOCGIFHWADDR ), &ifr )
                                                                 != failure ) {
                    found = true;
                    std::copy_n( ifr.ifr_hwaddr.sa_data, m_address.size(),
                                                           &m_address[ 0 ] ) ;
                }
            }
        }
        ++ it ;
    }

    if ( ! found ) {
        throw exception( "no suitable network adapter found" );
    }
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
