// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/testing/test_runner.hpp"

namespace breath {

test_runner::test_runner()
    : m_reporter( nullptr )
{
}

test_runner &
test_runner::instance()
{
    static test_runner  runner ;
    return runner ;
}

void
test_runner::attach_reporter( test_reporter & rep )
{
    m_reporter = &rep ;
}

int
test_runner::run( std::initializer_list< test_descriptor > list )
{
    return run( list.begin(), list.end() ) ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
