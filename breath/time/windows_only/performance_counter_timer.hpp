// =========================================================================
//                       Copyright 2006 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________
//
//!     \file
//!     \brief A timer policy using Windows' \c QueryPerformanceCounter().
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_xQJo3uSTt7ypxnH7y1CyRR3fJM5i3dsb
#define BREATH_GUARD_xQJo3uSTt7ypxnH7y1CyRR3fJM5i3dsb

namespace breath {

class performance_counter_timer
{
public:
    typedef long double duration_type ;
                        performance_counter_timer() ;

    void                restart() ;
    duration_type       elapsed() const ;
    duration_type       resolution() const ;

private:
    duration_type       m_start ;
    duration_type       m_frequency ;
} ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
