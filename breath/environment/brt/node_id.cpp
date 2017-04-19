// =========================================================================
//                    Copyright 2016-2017 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/porting/dependent_code.hpp"
#include BREATH_DEPENDENT_CODE( system, node_id.cpp )

#include "breath/environment/node_id.hpp"
#include "breath/stream/format_saver.hpp"
#include <iomanip>
#include <ostream>

namespace breath {

node_id const &
node_id::instance()
{
    static const node_id
                        id ;
    return id ;
}

uint8_t
node_id::operator []( int n ) const
{
    return m_address[ n ] ;
}

std::ostream &
operator <<( std::ostream & os, node_id const & id )
{
    format_saver const  saver( os ) ;

    os.setf( std::ios_base::uppercase ) ;
    os.setf( std::ios_base::hex, std::ios_base::basefield ) ;
    os.fill( '0' ) ;

    for ( auto it = id.m_address.cbegin() ; it != id.m_address.cend() ; ++ it ) {
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
