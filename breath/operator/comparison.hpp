// =========================================================================
//                       Copyright 2006 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________
//
//!     \file
//!     \brief Base class to provide inequality comparison operators.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_9eLHEHtKblEdQIGuXiqd2HmEUjrUscjf
#define BREATH_GUARD_9eLHEHtKblEdQIGuXiqd2HmEUjrUscjf


#include "breath/operator/equality_comparison.hpp"

namespace breath {

namespace adl_shield {

template< typename T >
class comparison
    :   private equality_comparison< T >
{
    friend bool         operator<( T const & lhs, T const & rhs )
    {
        return lhs.compare( rhs ) < 0 ;
    }
    friend bool         operator<=( T const & lhs, T const & rhs )
    {
        return lhs.compare( rhs ) <= 0 ;
    }
    friend bool         operator>( T const & lhs, T const & rhs )
    {
        return lhs.compare( rhs ) > 0 ;
    }
    friend bool         operator>=( T const & lhs, T const & rhs )
    {
        return lhs.compare( rhs ) >= 0 ;
    }
protected:
                        ~comparison() noexcept = default ;
} ;

}

using adl_shield::comparison ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
