// =========================================================================
//                    Copyright 2006-2008 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________
//
//!     \file
//!     \brief Hashing count policy.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_TFkXJUZ0hYDDlcmPKYMI9GfC5n42i9kF
#define BREATH_GUARD_TFkXJUZ0hYDDlcmPKYMI9GfC5n42i9kF

#include <stdexcept>

namespace breath {

class hashing_count
{
public:
    class exception ;

    enum type
    {
        wraps      = 1,
        is_limited
    } ;

    static void         on_length_exhausted( type t ) ;
} ;

// Intentionally we do not derive from std::length_error
class hashing_count::exception
    : public virtual std::logic_error
{
public:
    explicit            exception( char const * what_message ) ;
} ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
