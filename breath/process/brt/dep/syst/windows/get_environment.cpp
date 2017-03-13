// =========================================================================
//                       Copyright 2015 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/process/get_environment.hpp"
#include "breath/diagnostics/exception.hpp"
#include "breath/diagnostics/last_api_error.hpp"
#include "breath/process/program_status.hpp"
#undef UNICODE          // it seems impossible to directly call
                        // GetEnvironmentStringsA, so undefine UNICODE
#include <Windows.h>    // and use the normal name
#include <utility>

namespace {

// Note that program_status::instance() may throw; if so, the program
// is terminated. This is acceptable, because the program cannot run
// without a chance to manage its status.
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
get_environment()
{
    typedef std::map< std::string, std::string >
                        result_type ;
    char *              start = GetEnvironmentStrings() ;
    if ( start == nullptr ) {
        throw last_api_error( "GetEnvironmentStrings failed" ) ;
    }

    result_type         result ;
    try {
        char const *        curr = start ;
        while ( *curr != '\0' ) {
            std::string const   single = curr ;
            auto const          pos = single.find( '=' ) ;
            std::string const   name = single.substr( 0, pos ) ;
            // On my system the string pointed to by p begins with "=::=::\",
            // hence the test on empty.
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
