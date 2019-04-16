// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2006 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/time/c_clock_policy.hpp"
#include "breath/diagnostics/exception.hpp"

namespace breath {

std::clock_t
c_clock_policy::retrieve()
{
    std::clock_t const  ret( std::clock() ) ;
    return ret != ( static_cast< std::clock_t >( -1 ) )
        ? ret
        : throw breath::exception( "could not retrieve std::clock()" ) ;
}


c_clock_policy::c_clock_policy()
    :   m_start_tick() // just to remove compiler warnings
{
    restart() ;
}

void
c_clock_policy::restart()
{
    // synchronize our start
    std::clock_t const  s( retrieve() ) ;
    while ( s == ( m_start_tick = retrieve() ) ) { }
}

c_clock_policy::duration_type
c_clock_policy::elapsed() const
{
    double const        elapsed_ticks( retrieve() - m_start_tick ) ;

    //! gps - we should throw if elapsed < 0
    //!       and probably when elapsed == 0 too
    double const        elapsed_seconds( elapsed_ticks / CLOCKS_PER_SEC ) ;

    return 1000 * elapsed_seconds ;
}


c_clock_policy::duration_type
c_clock_policy::resolution() const
{
    std::clock_t        start ;
    std::clock_t        end ;

    std::clock_t const  s( retrieve() ) ;
    while ( s     == ( start = retrieve() ) ) { }
    while ( start == (   end = retrieve() ) ) { }

    return 1000.0 * ( end - start ) / CLOCKS_PER_SEC ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4: