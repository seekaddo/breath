// =========================================================================
//                       Copyright 2017 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/process/get_environment.hpp"
#include "breath/diagnostics/exception.hpp"
#include <unistd.h>

namespace breath {

std::map< std::string, std::string >
get_environment()
{
    typedef std::map< std::string, std::string >
                        result_type ;
    if ( environ == nullptr ) {
        // Can this really happen?
        throw exception( "environ is a null pointer" ) ;
    }

    result_type         result ;

    char const * const *
                        curr = environ ;
    while ( *curr != nullptr ) {
        std::string const   single = *curr ;
        auto const          pos = single.find( '=' ) ;
        std::string const   name = single.substr( 0, pos ) ;

        result.insert( result_type::value_type(
                            name,
                            single.substr( pos + 1 )
                        ) ) ;
        ++ curr ;
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
