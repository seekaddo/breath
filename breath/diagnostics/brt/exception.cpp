// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/diagnostics/exception.hpp"
#include "breath/counting/count.hpp"
#include <string.h>

namespace breath {

namespace {
    char const      incipit[] = "Breath library base exception" ;
}

exception::exception() noexcept
{
    strcpy( m_what_message, incipit ) ;
}

exception::exception( std::string const & what_msg ) noexcept
{
    char *              curr = &m_what_message[ 0 ] ;
    strcpy( curr, incipit ) ;
    curr += ( count(incipit) - 1 ) ;
    char const          sep[] = ": " ;
    strcpy( curr, sep ) ;
    curr += ( count(sep) - 1 ) ;
    strncpy( curr, what_msg.c_str(),
        what_message_max_size - (curr - &m_what_message[0] ) ) ;
}

char const *
exception::what() const noexcept
{
    return m_what_message ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
