// =========================================================================
//                    Copyright 2006-2007 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/cryptography/sha224_hasher.hpp"
#include "breath/cryptography/sha256_hasher.hpp"

namespace breath {

void
sha224_engine::init_state( state_type & state )
{
        state[ 0 ] = 0xc1059ed8 ;
        state[ 1 ] = 0x367cd507 ;
        state[ 2 ] = 0x3070dd17 ;
        state[ 3 ] = 0xf70e5939 ;
        state[ 4 ] = 0xffc00b31 ;
        state[ 5 ] = 0x68581511 ;
        state[ 6 ] = 0x64f98fa7 ;
        state[ 7 ] = 0xbefa4fa4 ;
}


void
sha224_engine::process_block( state_type & state, block_type const & block )
{
    return sha256_engine::process_block( state, block ) ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
