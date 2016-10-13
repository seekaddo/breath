// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________
//
//!     \file
//!     \brief Base64 encoding.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_m83AHFwUQlZBwnHisbdZpcYHaazyL2sn
#define BREATH_GUARD_m83AHFwUQlZBwnHisbdZpcYHaazyL2sn

#include <cstddef>

namespace breath {

//!     Converts a binary sequence to base64. Conforms to RFC 3548,
//!     except that it allows to line-wrap the generated base64 output
//!     (\c wrap_column != 0).
//!
//!     \param[in]  begin Iterator to the first element of the binary
//!                 sequence
//!     \param[in]  end   One-past-the-end iterator in the binary
//!                 sequence
//!     \param[out] out   Iterator to the first element of the base64
//!                 output
//!     \param[in]  wrap_column Column where line-wrapping must happen
//!                 in the generated output (0 means "no wrapping")
// -------------------------------------------------------------------------
template< typename InputIter, typename OutputIter >
void                binary_to_base64( InputIter begin, InputIter end,
                                      OutputIter out,
                                      std::size_t wrap_column = 0 ) ;

}

#include "brt/binary_to_base64.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
