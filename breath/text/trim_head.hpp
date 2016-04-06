// =========================================================================
//                       Copyright 2011 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include <string>

namespace breath {

// gps dovrebbe rimuovere gli space secondo il locale?
// più in là cmq userò una mia set_of_char, costruibile a sua volta
// da una stringa
//
std::string         trim_head( std::string const & source,
                               std::string const & to_remove = " \t" ) ;

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
