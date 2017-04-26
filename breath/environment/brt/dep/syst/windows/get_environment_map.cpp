// =========================================================================
//                       Copyright 2015 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/environment/get_environment_map.hpp"
#include "breath/diagnostics/exception.hpp"
#include "breath/diagnostics/last_api_error.hpp"
#include "breath/process/program_status.hpp"
#undef UNICODE          // it seems impossible to directly call
                        // GetEnvironmentStringsA, so undefine UNICODE
#include <Windows.h>    // and use the normal name
#include <utility>

namespace {

void
do_free( char * p ) noexcept
{
    using               breath::program_status ;
    if ( FreeEnvironmentStrings( p ) == 0 ) {
        program_status::instance().declare_error( program_status::warning ) ; //gps
    }
}

}

namespace breath {

std::map< std::string, std::string >
get_environment_map()
{
    typedef std::map< std::string, std::string >
                        result_type ;
    
    result_type         result ;
    char *              start = GetEnvironmentStrings() ;
    if ( start == nullptr ) {
        throw last_api_error( "GetEnvironmentStrings() failed" ) ;
    }

    try {
        char const *        curr = start ;
        while ( *curr != '\0' ) {
            std::string const   single = curr ;
            auto const          pos = single.find( '=' ) ;
            std::string const   name = single.substr( 0, pos ) ;
            // On my system the string pointed to by start begins with
            // "=::=::\", hence the test on empty().
            if ( ! name.empty() ) {
                result.insert( result_type::value_type(
                                    name,
                                    single.substr( pos + 1 )
                                ) ) ;
            }
            curr += ( single.length() + 1 ) ;
        }
    } catch ( ... ) {
        do_free( start ) ;
        throw ;
    }
    do_free( start ) ;
    return result ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
