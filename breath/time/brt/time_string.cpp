// =========================================================================
//                    Copyright 2008-2011 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/time/time_string.hpp"
#include "breath/idiom/maybe.hpp"
#include <ctime>

namespace breath {

//      time_string:
//      ------------
//
//      IMPLEMENTATION NOTE:
//      --------------------
//      Intentionally I used a fixed size buffer here: the size is
//      plentiful for any date formatting need I could imagine, and
//      anything which involved dynamic allocation looked definitely
//      like over-engineering.
// ---------------------------------------------------------------------------
maybe< std::string >
time_string( std::string const & format, time_string_zone::zone zone )
{
    using namespace std ;
    maybe< string >     result ;

    time_t const        time_stamp( time( nullptr ) ) ;
    if ( time_stamp != static_cast< time_t >( -1 ) ) { // gps
        tm const * const    broken_down( zone == time_string_zone::utc
                                            ? gmtime(    &time_stamp )
                                            : localtime( &time_stamp ) ) ;
        if ( broken_down != nullptr ) {
            std::size_t const   max_size( 256 ) ;
            char                buffer[ max_size ] = { 0 } ;
            if ( strftime( buffer, max_size, format.c_str(), broken_down )
                    != 0 ) {
                result = buffer ;
            }
        }
    }
    return result ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
