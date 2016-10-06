// =========================================================================
//                       Copyright 2013 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________
//
//!     \file
//!     \brief Displays an expression to \c std::cout.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_v4ifHvyokFutGDGkksKs5kPv6rpDcUGv
#define BREATH_GUARD_v4ifHvyokFutGDGkksKs5kPv6rpDcUGv

#include "breath/preprocessing/stringize_delayed.hpp"
#include <iostream>
#include <ostream> // not necessary in C++11
#include <cstring>

//!     A simple macro for quickly displaying a variable to \c std::cout.
//!     It was born as "DUMP_VARIABLE()" but then I immediately found
//!     a [gps "an"?] usage where I wanted to display something like
//!     `i + j', so I've renamed it to "DUMP_EXPRESSION".
//!
//!     It's intended that you use this just for quick and dirty
//!     checks, and that you *remove* it after that!
//!
//!     NOTE: the #includes are not part of the interface.
//!
//!     NOTE2: macros within the argument `expr' are expanded
// ---------------------------------------------------------------------------
#define BREATH_DUMP_EXPRESSION( expr )                                        \
        do {                                                                  \
            std::cout << BREATH_STRINGIZE_DELAYED( expr ) " = " << ( expr ) ; \
            if ( std::strcmp( #expr,                                          \
                              BREATH_STRINGIZE_DELAYED( expr ) ) != 0 ) {     \
                std::cout << " [from " << #expr << "]" ;                      \
            }                                                                 \
            std::cout << std::endl ;                                          \
        } while ( false )                                                  /**/

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
