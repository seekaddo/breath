// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
//
// _________________________________________________________________________

#include "breath/testing/console_reporter.hpp"
#include "breath/testing/test_exception.hpp"
#include <ostream>
#include <iostream >

namespace breath {

console_reporter::console_reporter( std::ostream & os )
    :   m_stream( os )
{
}

void
console_reporter::on_all_tests_begin()
{
    m_stream << "Unit tests:" << std::endl;
    m_passed = 0;
    m_failed = 0;
    m_unexpected_exceptions = 0;
}

void
console_reporter::on_all_tests_end()
{
    m_stream << std::endl << "Passed: " << m_passed << ", failed: " << m_failed
                          << ", unexp. exceptions: " << m_unexpected_exceptions
                          << std::endl ;
}

void
console_reporter::on_test_begin( int test_number, char const * )
{
    m_stream << "[" << test_number << "=" ;
}

void
console_reporter::on_test_passed( int )
{
    m_stream << "P]" ;
    ++ m_passed ;
}
void
console_reporter::on_test_failed(int, const test_exception & ex )
{
    m_stream << "F (" << ex.filename() << ":" << ex.line() << ")]" ;
    ++ m_failed ;
}

void
console_reporter::on_unexpected_exception( int )
{
    m_stream << "X]" ;
    ++m_unexpected_exceptions ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
