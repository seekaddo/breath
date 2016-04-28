// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/conversion/roman.hpp"
#include "breath/diagnostics/assert.hpp"
#include <ostream>

namespace breath {

roman::roman( int n )
{
    BREATH_ASSERT( 1 <= n && n <= 3999 ) ;

    struct table
    {
        int                 value ;
        char const *        repr ;
    } const table[] = {
       { 1000, "M" },
        { 900, "CM" }, { 500, "D" }, { 400, "CD" }, { 100, "C" },
         { 90, "XC" },  { 50, "L" },  { 40, "XL" },  { 10, "X" },
          { 9, "IX" },   { 5, "V" },   { 4, "IV" },   { 1, "I" },
          { 0, nullptr } 
    } ;

    m_representation.reserve( 15 ) ;
    struct table const * p = &table[ 0 ] ;
    for ( ; p->value != 0 ; ++ p ) {
        int                 value = n / p->value;
        n %= p->value;
        while ( value != 0 ) {
            m_representation += p->repr ;
            -- value ;
        }
    }
}

std::ostream &
operator<<( std::ostream & os, roman const & r )
{
    return os << r.m_representation ;
}
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
