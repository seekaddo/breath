// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________
//
//      Base64 encoding, conforming to RFC 3548.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_m83AHFwUQlZBwnHisbdZpcYHaazyL2sn
#define BREATH_GUARD_m83AHFwUQlZBwnHisbdZpcYHaazyL2sn

namespace breath {

template< typename InputIter, typename OutputIter >
void                binary_to_base64( InputIter begin, InputIter end,
                                      OutputIter out ) ;

}

#include "brt/binary_to_base64.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
