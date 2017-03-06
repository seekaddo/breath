// =========================================================================
//                       Copyright 2006 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________
//
//!     \file
//!     \brief A clock device based on \c std::clock().
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_s9RhTgkTQviSRQ89lVvZRW16hRqlr1OA
#define BREATH_GUARD_s9RhTgkTQviSRQ89lVvZRW16hRqlr1OA

#include <ctime>

namespace breath {


//      c_clock_device
//      ==============
//
//!     Note that on some (non-conforming) implementations
//!     std::clock() will actually measure wall-clock time.
// ---------------------------------------------------------------------------
class c_clock_device
{
public:
    typedef double      duration_type ;

                        c_clock_device() ;

    void                restart() ;
    duration_type       elapsed() const ;

    //! Returns an estimate of the timer resolution, in ms.
    //! May return slightly different values from call to call.
    // -----------------------------------------------------------------------
    duration_type       resolution() const ;

private:
    static std::clock_t retrieve() ;

private:
    std::clock_t        m_start_tick ;
} ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
