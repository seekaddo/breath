// =========================================================================
//                       Copyright 2013 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________
//
//!     \file
//!     \brief Displays an expression to \c std::cout.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_v4ifHvyokFutGDGkksKs5kPv6rpDcUGv
#define BREATH_GUARD_v4ifHvyokFutGDGkksKs5kPv6rpDcUGv

#include "breath/preprocessing/stringize_delayed.hpp"
#include <cstring>
#include <iostream>
#include <ostream> // not necessary in C++11

//!     A simple macro for quickly dumping a variable to \c std::cout.
//!     It was born as "DUMP_VARIABLE()" but then I immediately found
//!     a usage where I wanted to display something like `i + j', so
//!     I've renamed it to "DUMP_EXPRESSION".
//!
//!     It's intended that you use this just for quick and dirty
//!     checks, and that you *remove* it after that!
//!
//!     The expression is shown in the form <expression> = value. If
//!     expression contains macro invocations, the unexpanded form
//!     is displayed, too.
//!
//!     NOTE: the #includes are not part of the interface.
//!
//!     NOTE2: macros within the argument `expr' are expanded.
// ---------------------------------------------------------------------------
#define BREATH_DUMP_EXPRESSION( expr )                                        \
        do {                                                                  \
            std::ostream &          os = std::cout ;                          \
            os << BREATH_STRINGIZE_DELAYED( expr ) " = " << ( expr ) ;        \
            if ( std::strcmp( #expr,                                          \
                              BREATH_STRINGIZE_DELAYED( expr ) ) != 0 ) {     \
                os << " [from: " << #expr << ']' ;                            \
            }                                                                 \
            os << std::endl ;                                                 \
        } while ( false )                                                  /**/

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
