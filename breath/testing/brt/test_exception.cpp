// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/testing/test_exception.hpp"

namespace breath {

test_exception::test_exception( char const * filename,
                                unsigned long line ) noexcept
    : exception(), m_filename( filename ), m_line( line )
{
}

test_exception::test_exception( std::string const & str,
                                char const * filename,
                                unsigned long line ) noexcept
    : exception( str ), m_filename( filename ), m_line( line )
{
}

char const *
test_exception::filename() const noexcept
{
    return m_filename ;
}

unsigned long
test_exception::line() const noexcept
{
    return m_line ;
}

std::ostream &
operator <<(std::ostream & os, test_exception const & ex )
{
    return os << ex.what() << " : " << ex.filename() << ", " << ex.line() ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
