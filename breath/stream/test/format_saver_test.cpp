// =========================================================================
//                       Copyright 2015 Gennaro Prota
//
//                  Licensed under the BSD-X License. [gps]
//                (See accompanying file BSD-X_LICENSE.txt or
//             <http://opensource.org/licenses/bsd-license.php>)
// _________________________________________________________________________

#include "breath/stream/format_saver.hpp"
#include <iomanip>
#include <sstream>

///
#include "breath/diagnostics/assert.hpp"
#define DO_TEST( x )  BREATH_ASSERT( x )

/////////
int
main()
{
    using breath::format_saver ;
    std::stringstream   str ;
    {
        format_saver        saver( str );
        str.setf( std::ios::hex, std::ios::basefield ) ;
        str.fill( '0' ) ;
        str << std::setw( 2 ) << 15 ;
        DO_TEST( str.str() == "0f" ) ;
        //std::string         discard ;
        //str >> discard ;
    }
    DO_TEST( (str.flags() & std::ios::hex) == 0 ) ;
    DO_TEST( str.fill() == ' ' );
    //str << 5 ;
    //std::string Temp=str.str();
    //DO_TEST( str.str() == "5" ) ;
}






// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
