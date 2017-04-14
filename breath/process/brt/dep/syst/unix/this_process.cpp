// =========================================================================
//                       Copyright 2015 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/diagnostics/assert.hpp"
#include "breath/diagnostics/last_api_error.hpp"
#include "breath/memory/auto_array.hpp"
#include <unistd.h>
#include <errno.h>
#include <string>

namespace breath {

this_process::this_process()
{
}

this_process &
this_process::instance()
{
    static this_process * inst ;
    if ( inst == nullptr ) {
        inst = new this_process() ;
    }
    return *inst ;

}

std::string
this_process::current_directory()
{
    std::size_t         sz = 512 ;
    auto_array< char >  aa ;

    char const *        p = nullptr ;
    do {
        sz *= 2 ;
        aa.reset( new char[ sz ] ) ;
        p = getcwd( aa.get(), sz ) ;
    } while ( p == nullptr && errno == ERANGE  ) ;

    if ( p == nullptr ) {
        throw last_api_error( "getcwd() failed" ) ;
    }
    return std::string( p );
}

void
this_process::set_current_directory( std::string const & /*dir*/ )
{
    BREATH_ASSERT( false && "not implementable?" );
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
