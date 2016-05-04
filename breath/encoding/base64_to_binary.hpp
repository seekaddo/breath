// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________
//
//      Base64 decoding, conforming to RFC 3548.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_ubEInhYBWjgftwkYlSFbSOFcFUILqJgK
#define BREATH_GUARD_ubEInhYBWjgftwkYlSFbSOFcFUILqJgK

namespace breath {

//      This function conforms to RFC 3548 with one exception: it
//      allows newlines to appear anywhere in the input.
//      It throws an exception on any other invalid input character.
// ---------------------------------------------------------------------
template< typename InputIter, typename OutputIter >
void                base64_to_binary( InputIter begin, InputIter end,
                                      OutputIter out ) ;

}

#include "brt/base64_to_binary.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
