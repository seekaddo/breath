// =========================================================================
//                       Copyright 2006 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/time/c_clock_device.hpp"
#include "breath/diagnostics/exception.hpp"

namespace breath {

 
std::clock_t
c_clock_device::retrieve()
{
    std::clock_t const  ret( std::clock() );
    return ret != ( static_cast< clock_t >( -1 ) )
        ? ret
        : throw breath::exception( "could not retrieve std::clock()" ) ;
}
 

c_clock_device::c_clock_device()
    : m_start_tick() // just to remove compiler warnings
{
    restart() ;
}

void c_clock_device::restart()
{
    // synchronize our start
    std::clock_t const  s( retrieve() ) ;
    while( s == ( m_start_tick = retrieve() ) )
    {}
}

c_clock_device::duration_type
c_clock_device::elapsed() const
{
    double const        elapsed_ticks( retrieve() - m_start_tick );

    //! gps - we should throw if elapsed < 0
    //!       and probably when elapsed == 0 too
    double const        elapsed_seconds( elapsed_ticks / CLOCKS_PER_SEC);

    return 1000 * elapsed_seconds ;
}


c_clock_device::duration_type
c_clock_device::resolution() const
{
    std::clock_t start;
    std::clock_t end;

    std::clock_t const  s( retrieve() ) ;
    while( s     == ( start = retrieve() ) ) { }
    while( start == (   end = retrieve() ) ) { }

    return 1000.0 * ( end - start ) / CLOCKS_PER_SEC;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
