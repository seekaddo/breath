// =========================================================================
//                       Copyright 2006 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/time/windows_only/performance_counter_timer.hpp"
#include "breath/diagnostics/exception.hpp"
#include "breath/diagnostics/last_api_error.hpp"
#include <Windows.h>

namespace breath {

performance_counter_timer::performance_counter_timer()
{
    // Note that restart() is not called here. It will be called by
    // elapsed_timer<>, if needed. Note that this causes the member
    // m_start to be left uninitialized.
    //
    LARGE_INTEGER       f;
    if( QueryPerformanceFrequency( &f ) == 0 ) {
        throw last_api_error( "QueryPerformanceFrequency failed" ) ;
    }
    m_frequency = static_cast< duration_type >( f.QuadPart ) ;
}

void
performance_counter_timer::restart()
{
    LARGE_INTEGER       li ;
    if ( QueryPerformanceCounter( &li ) == 0 ) {
        throw last_api_error( "QueryPerformanceCounter failed" ) ;
    }
    m_start = static_cast< duration_type >( li.QuadPart ) ;

}

performance_counter_timer::duration_type
performance_counter_timer::elapsed() const
{
    LARGE_INTEGER       li ;
    if ( QueryPerformanceCounter( &li ) == 0 ) {
        throw last_api_error( "QueryPerformanceCounter failed" ) ;
    }
    return ( li.QuadPart - m_start ) * resolution() ;
}

performance_counter_timer::duration_type
performance_counter_timer::resolution() const
{
    // resolution is in milliseconds
    return 1000.0 / m_frequency;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
