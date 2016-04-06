// =========================================================================
//                       Copyright 2015 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/diagnostics/assert.hpp"
#include "breath/memory/auto_array.hpp"
#include <unistd.h>
#include <errno.h>

namespace breath {

this_process &
this_process::instance()
{
    static this_process * inst ;
    if ( inst == nullptr ) {
        inst = new this_process( getpid() ) ;
    }
    return *inst ;

}

std::string
this_process::current_directory() const
{
    std::size_t sz = 512 ;
    auto_array< char > aa ;

    do {
        sz *= 2 ;
        aa.reset( new char[ sz ] ) ;
        char const * const
                        p = getcwd( aa.get(), sz ) ;
    } while ( p == nullptr && errno == ERANGE  ) ;

    if ( p == nullptr ) {
        throw last_api_error( "getcwd failed" ) ;
    }
    return std::string( p );
}

void
this_process::set_current_directory( std::string const & dir )
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
