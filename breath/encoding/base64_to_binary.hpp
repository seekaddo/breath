// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________
//
//!     \file
//!     \brief Base64 decoding.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_ubEInhYBWjgftwkYlSFbSOFcFUILqJgK
#define BREATH_GUARD_ubEInhYBWjgftwkYlSFbSOFcFUILqJgK

namespace breath {

//!     Decodes a base64 representation.
//!
//!     This function conforms to RFC 3548 with one exception: it
//!     allows newlines to appear anywhere in the input.
//!     It throws a \c breath::exception on any other invalid input
//!     character.
//!
//!     \param[in] begin Iterator to the first element of the base64
//!                      sequence
//!     \param[in] end   One-past-the-end iterator in the same
//!                      sequence
//!     \param[out] out  Iterator to the first element of the output
//!                      sequence (binary)
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
