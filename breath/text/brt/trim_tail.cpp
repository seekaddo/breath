// =========================================================================
//                       Copyright 2008 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/text/trim_tail.hpp"

namespace breath {

std::string
trim_tail( std::string const & str )
{
    return breath::trim_tail( str, set_of_chars( " \t" ) ) ;
}


std::string
trim_tail( std::string const & str,
           breath::set_of_chars const & to_remove )
{
    auto const          pos =
        str.find_last_not_of( to_remove.as_string() ) ;

    return str.substr( 0, pos + 1 ) ; // note that this is well defined
                                      // for pos == npos
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
