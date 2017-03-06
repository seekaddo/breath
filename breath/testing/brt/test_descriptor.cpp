// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/testing/test_descriptor.hpp"

namespace breath {

test_descriptor::test_descriptor( void( &f )(), char const * name ) noexcept
    : m_function( f ), m_name( name )
{
}

test_descriptor::test_function
test_descriptor::function() const noexcept
{
    return m_function ;
}

std::string
test_descriptor::name() const noexcept
{
    return m_name ;
}
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
