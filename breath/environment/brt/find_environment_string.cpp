// =========================================================================
//                    Copyright 2006-2007 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/environment/find_environment_string.hpp"
#include "breath/idiom/maybe.hpp"

#include <cstdlib>

namespace breath {

maybe< std::string >
find_environment_string( string_argument const & name )
{
    typedef maybe< std::string > maybe_type;

    char const * const  p( std::getenv( name.value().c_str() ) );

    return p == nullptr
        ? maybe_type()
        : maybe_type( std::string( p ) )
        ;
    }
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
