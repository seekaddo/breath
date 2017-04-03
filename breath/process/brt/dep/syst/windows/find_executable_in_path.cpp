// =========================================================================
//                       Copyright 2015 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/process/find_executable_in_path.hpp"
#include "breath/diagnostics/assert.hpp"
#include "breath/environment/find_environment_string.hpp"
#include "breath/path/extension.hpp"
#include "breath/text/split.hpp"

#include <string>
#include <vector>
#include <Windows.h>

namespace breath {

maybe< std::string >
find_executable_in_path( std::string const & name,
                         maybe< std::string > const & path )
{
    BREATH_ASSERT( ! name.empty() ) ;

    std::string         extensions = breath::extension( name ) ;
    if ( extensions.empty() ) {
        extensions = find_environment_string( "PATHEXT" ).value() ;
    }

    std::vector< std::string > const &
                        e = breath::split( extensions, ';' ) ;
    bool                found = false;
    char                fullpath[ MAX_PATH ] ;
    for( auto it = e.begin() ; it != e.end() ; ++it ) {
        if( SearchPathA( path.is_valid()
                            ? path.value().c_str()
                            : nullptr,
                         name.c_str(),
                         it->c_str(),
                         sizeof fullpath,
                         &fullpath[ 0 ],
                         nullptr
                    ) != 0 ) {
            found = true;
            break ;
        }
    }
    return found
            ? maybe< std::string >( std::string( fullpath ) )
            : maybe< std::string >()
            ;
}



}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
