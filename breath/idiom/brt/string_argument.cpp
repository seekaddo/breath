// =========================================================================
//                       Copyright 2015 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/idiom/string_argument.hpp"
#include "breath/diagnostics/assert.hpp"

namespace breath {

string_argument::string_argument( std::string const & s )
    : m_value( s )
{
}

string_argument::string_argument( char const * p )
    : m_value( ( BREATH_ASSERT( p != nullptr ), p ) )
{
}

std::string
string_argument::value() const
{
    return m_value ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
