// =========================================================================
//                       Copyright 2008 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/text/split.hpp"

namespace breath {

std::vector< std::string >
split( std::string const & s, char c )
{
    std::vector< std::string >
                        result ;

    for ( auto it = s.cbegin() ; it != s.cend() ; ) {
        auto const          curr =  it ;
        while ( it != s.cend() && *it != c ) {
            ++ it ;
        }
        result.push_back( std::string( curr, it ) ) ;
        if ( it != s.cend() ) {
            ++ it ;
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
