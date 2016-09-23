// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________
//
//!     \file
//!     \brief The integer part of the log, base 2, of its argument.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_Kym3FA1ex9fw5x3d1rVgY686BX4YRKvw
#define BREATH_GUARD_Kym3FA1ex9fw5x3d1rVgY686BX4YRKvw

#include <cstdint>

namespace breath {

//!     The behavior is undefined if x == 0 (and might result in an
//!     assertion failure). Otherwise the function returns the integer
//!     part of the logarithm, base 2, of its argument.
//!
//!     NOTE:  this constexpr function supersedes meta::integer_log2,
//!            which is declared deprecated.
//!     NOTE2: this function does not compile with Visual C++ 2015 (=
//!            v14) because it does not yet implement constexpr
//!            functions in all their power.
// --------------------------------------------------------------------
constexpr int       integer_log2( std::uintmax_t x ) noexcept ;

}

#include "brt/integer_log2.tpp"
#endif
// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
