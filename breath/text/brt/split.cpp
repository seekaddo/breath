// =========================================================================
//                    Copyright 2008-2019 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/text/split.hpp"

namespace breath {

std::vector< std::string >
split( std::string const & s, std::string const & delimiters )
{
    std::vector< std::string >
                        result ;

    for ( std::string::size_type i = 0 ; i < s.size() ; ++ i ) {
        auto const          start = i ;
        i = s.find_first_of( delimiters, i );
        if ( i == s.npos ) {
            i = s.size() ;
        }
        result.emplace_back( s.cbegin() + start, s.cbegin() + i ) ;
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
