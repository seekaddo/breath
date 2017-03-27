// =========================================================================
//                       Copyright 2015 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________
//
//!     \file
//!     \brief A string with non-printable chars escaped.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_03plpMI2VjgMEb2QhWRYStxFLQ2UshCk
#define BREATH_GUARD_03plpMI2VjgMEb2QhWRYStxFLQ2UshCk

#include "breath/idiom/maybe.hpp"
#include <iosfwd>
#include <string>

namespace breath {

class printable_string
{
public:
    explicit            printable_string( char const * ) ;
    explicit            printable_string( std::string const & ) ;

private:

    friend std::ostream &
                    operator <<( std::ostream & dest,
                                 printable_string const &) ;

    maybe< std::string >
                        m_value ;
} ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
