// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/text/tail.hpp"
#include "breath/diagnostics/assert.hpp"

namespace breath_ns {

std::string
tail( std::string const & s, std::ptrdiff_t count )
{
    BREATH_ASSERT( count >= 0 ) ;

    std::ptrdiff_t const
                        length = s.length() ;

    //      Note how the first argument to substr() *may* be equal to
    //      length (count == 0).
    // -----------------------------------------------------------------------
    return count >= length
                ? s
                : s.substr( length - count )
                ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
