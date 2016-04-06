// =========================================================================
//                    Copyright 2006-2007 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#ifndef BREATH_GUARD_wCcpHSPgQuuMlLcoiraq0109Dj5dIMnV
#define BREATH_GUARD_wCcpHSPgQuuMlLcoiraq0109Dj5dIMnV

/*! \file   sha512_hasher.hpp
    \brief
        SHA-512 templates
*/

#include "breath/cryptography/merkle_damgard_engine.hpp"
#include "breath/cryptography/merkle_damgard_hasher.hpp"

namespace breath {

class sha512_engine ;

template< typename Hasher >
class digest ;

//!
//! convenience typedefs
//!
typedef merkle_damgard_machine< sha512_engine > sha512_hasher ;
typedef digest< sha512_hasher >                 sha512_digest ;



class sha512_engine
    : public merkle_damgard_engine< 512, 1024, big_endian_policy, 64 >
{
public:
    static void init_state( state_type & state ) ;
    static void process_block( state_type & state, block_type const & block ) ;
} ;


}


#endif
// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
