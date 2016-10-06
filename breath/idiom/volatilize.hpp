// =========================================================================
//                    Copyright 2006-2007 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________
//
//!     \file
//!     \brief Adds a \c volatile qualification.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_4VpDkPMRFQlDZhFnubC67vt6hSC6EvrJ
#define BREATH_GUARD_4VpDkPMRFQlDZhFnubC67vt6hSC6EvrJ

/*!
        Little helper to add \c volatile qualification to an lvalue
        expression without using \c static_cast (which might be too
        powerful) and without breaking the expression in two parts.
*/

namespace breath {


template< typename T >
T volatile &
volatilize( T & ref )
{
    return ref ;
}


}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
