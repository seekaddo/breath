// =========================================================================
//                       Copyright 2015 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________
//
//!     \file
//!     \brief Finds an executable file in a given path.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_FY2GqgDJYLYk2fqwzgZI8Nhxv6QAdsQW
#define BREATH_GUARD_FY2GqgDJYLYk2fqwzgZI8Nhxv6QAdsQW

#include "breath/idiom/maybe.hpp"
#include <string>

namespace breath {

maybe< std::string >
                    find_executable_in_path(
                        std::string const & name,
                        maybe< std::string > const & path =
                                                maybe< std::string >() ) ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
