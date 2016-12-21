// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/environment/node_id.hpp"
#include "breath/diagnostics/exception.hpp"
#include "breath/memory/auto_array.hpp"
#include "breath/stream/format_saver.hpp"
#include <iomanip>
#include <ostream>
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
        throw exception( "cannot get adapters info" ) ;
    }
    bool                found = false ;
    while ( info != nullptr && ! found ) {
        if ( info->Type == MIB_IF_TYPE_ETHERNET
                && info->AddressLength == m_address.size() ) {

            found = true ;
            for ( unsigned i = 0 ; i < m_address.size() ; ++ i ) {
                m_address[ i ] = info->Address[ i ] ;
            }
        }
        info = info->Next ;
    }
}

node_id const &
node_id::instance()
{
    static const node_id
                        id ;
    return id ;
}

uint8_t
node_id::operator[]( int n ) const
{
    return m_address[ n ] ;
}

std::ostream &
operator <<( std::ostream & os, node_id const & id )
{
    format_saver const  saver( os ) ;

    os.setf( std::ios_base::uppercase ) ;
    os.setf( std::ios_base::hex, std::ios_base::basefield ) ;

    for ( auto it = id.m_address.cbegin(); it != id.m_address.cend() ; ++ it ) {
        os << std::setw( 2 ) << static_cast< int >( *it ) ;
        if ( it != ( id.m_address.cend() - 1 ) ) {
            os << '-' ;
        }
    }
    return os ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
