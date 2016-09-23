// =========================================================================
//                       Copyright 2006 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________
//
//!     \file
//!     \brief Returns the filename part of a path.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_t4h0OWeS8sua5gWE50YSmGUx15Kw2wrR
#define BREATH_GUARD_t4h0OWeS8sua5gWE50YSmGUx15Kw2wrR

#include "breath/idiom/string_argument.hpp"
#include <string>

namespace breath {

//!         Returns the filename part of a path. Assumes that the path
//!         is well-formed.
//! -------------------------------------------------------------------
std::string         base_filename( string_argument const & full_path ) ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
