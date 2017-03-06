// =========================================================================
//                    Copyright 2006-2007 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________
//
//!     \file
//!     \brief  SHA-1 function.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_lTc6ZJg4kodcuFjtlYBwwj0hqDplySkG
#define BREATH_GUARD_lTc6ZJg4kodcuFjtlYBwwj0hqDplySkG

#include "breath/cryptography/merkle_damgard_engine.hpp"
#include "breath/cryptography/merkle_damgard_hasher.hpp"


namespace breath {

class sha1_engine ;

template< typename Hasher >
class digest ;

//!
//! convenience typedefs
//!
typedef merkle_damgard_machine< sha1_engine > sha1_hasher ;
typedef digest< sha1_hasher >                 sha1_digest ;


//!
//! SHA-1 policy class for Merkle Damgard machine
//!
class sha1_engine
    : public merkle_damgard_engine< 160, 512, big_endian_policy >
{
public:
    static void     init_state( state_type & state ) ;
    static void     process_block( state_type & state,
                                    block_type const & block ) ;

} ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
