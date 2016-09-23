// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________
//
//!     \file
//!     \brief Roman numerals.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_hMt6bmZCT9RIwijJe5QSttMMotHJsr1N
#define BREATH_GUARD_hMt6bmZCT9RIwijJe5QSttMMotHJsr1N

#include <iosfwd>
#include <string>

namespace breath {

class roman
{
public:
    explicit            roman( int n ) ;

private:
    std::string         m_representation ;

    friend std::ostream &
        operator<<( std::ostream &, roman const & ) ;
} ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
