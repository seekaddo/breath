// =========================================================================
//                    Copyright 2006-2008 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/cryptography/hashing_count.hpp"

namespace breath {

hashing_count::exception::exception( char const * message )
    : std::logic_error( message )
{
}

void
hashing_count::on_length_exhausted( hashing_count::type t )
{
    if ( t == hashing_count::is_limited )
        throw hashing_count::exception(
                "input too long for this hash function" ) ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
