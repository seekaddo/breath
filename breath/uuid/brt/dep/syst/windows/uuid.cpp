// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/uuid/uuid.hpp"
#include "breath/counting/count.hpp"
#include "breath/diagnostics/assert.hpp"
#include "breath/environment/node_id.hpp"
#include "breath/random/entropy_source.hpp"
#include "breath/stream/format_saver.hpp"

#include <cinttypes>
#include <climits>
#include <cstddef>
#include <ostream>
#include <Windows.h>

namespace breath {

uuid::uuid( uuid::variant var, uuid::version ver )
{
    // other variants/versions not implemented
    BREATH_ASSERT( var == rfc_4122 && ver == time_based ) ;

    // NT keeps time in FILETIME format, which is 100ns ticks since
    // Jan 1, 1601.  UUIDs use time in 100ns ticks since Oct 15, 1582.
    // The difference is 17 Days in Oct + 30 (Nov) + 31 (Dec)
    // + 18 years and 5 leap days.
    //
    FILETIME            ft ;
    ::GetSystemTimeAsFileTime( &ft ) ;
    std::uint64_t const time_stamp = reinterpret_cast< std::uint64_t const & >( ft ) +
                                     std::uint64_t( 1000 * 1000 * 10 )
                                   * std::uint64_t( 60 * 60 * 24 )
                                   * std::uint64_t( 17 + 30 + 31 + 365 * 18 + 5 ) ;

    m_time_low = time_stamp & 0xFFFF'FFFF ;
    m_time_mid = (time_stamp >> 32) & 0xFFFF ;
    m_time_hi_and_version = ( (time_stamp >> 48) & 0x0FFF ) + ( 1 << 12 ) ;
    entropy_source      es ;
    std::uint32_t const rnd = ( es.next() << 24 ) | ( es.next() << 16 )
                            | ( es.next() << 8 )  |   es.next() ;
    m_clock_seq = ( ( rnd >> 4 ) & 0x3fff ) | 0x8000 ;

    for (std::size_t i = 0 ; i < breath::count( m_node ) ; ++ i ) {
        m_node[i] = node_id::instance()[ static_cast< int >( i ) ] ;
    }
}

template< typename T >
std::ostream &
output_as_hex( std::ostream & os, T t )
{
    static_assert( CHAR_BIT == 8, "" ) ;
    os << std::hex << std::nouppercase ;
    for ( std::size_t shift_amount = sizeof t * CHAR_BIT ; shift_amount > 0 ;
                                            shift_amount -= CHAR_BIT ) {
        uint8_t const       byte = t >> ( shift_amount - CHAR_BIT ) & 0xFF ;
        os << ( byte >> ( CHAR_BIT / 2 ) ) ;
        os << ( byte & 0x0f ) ;
    }
    return os ;
}
std::ostream & operator <<( std::ostream & os, uuid const & uu )
{
    format_saver const  saver( os ) ;
    output_as_hex( os, uu.m_time_low ) << '-' ;
    output_as_hex( os, uu.m_time_mid ) << '-' ;
    output_as_hex( os, uu.m_time_hi_and_version ) << '-' ;
    output_as_hex( os, uu.m_clock_seq ) << '-' ;
    for ( std::size_t i = 0; i < count( uu.m_node ) ; ++ i ) {
        os << static_cast< int >( uu.m_node[ i ] ) ;
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
