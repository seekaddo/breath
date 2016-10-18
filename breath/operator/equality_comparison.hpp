// =========================================================================
//                       Copyright 2006 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________
//
//!     \file
//!     \brief Base class to provide equality comparison operators.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_FVjQpxOUioJICCQIoTK5TmuA8UEe4UzI
#define BREATH_GUARD_FVjQpxOUioJICCQIoTK5TmuA8UEe4UzI

/*!
        Automatically provides a definition for \c operator==() and
        \c operator!=() in terms of a user-declared member function
        \c %is_equal().
*/

namespace breath {
namespace adl_shield {

//!     The class template \c equality_comparison<> provides \c
//!     operator== and \c operator!= as namespace scope functions
//!     whose name is associated "on demand" (i.e. at instantiation)
//!     to class \c T, via ADL.
//!
//!     Usage:
//!     ======
//!
//!      - Provide an %is_equal() function for your class \c C.
//!
//!      - Add <code>equality_comparison< C ></code> as a private base
//|        class of \c C.
//!
//!     As a result, \c== and \c != will be available too for class \c
//!     C and defined in terms of is_equal.
//!
//!     ADL protection:
//!     ===============
//!
//!     Even though this uses the Barton-Nackman idiom and relies on
//!     its standard-conforming, ADL-based, mechanics (no friend
//!     injection), it is protected from ADL in namespace breath
//!     in a way which allows only the provided operator function to
//!     be found.
//!     This means that you can safely derive your own type \c C
//!     from any of its instantiations \b without risk of ADL picking
//!     up anything \e unintended in \c namespace \c breath. Example:
//!         <example TODO:>
//!
//!     Naming rationale:
//!
//!     The name of the class template indicates the kind of
//!     comparison that its target will support. This leads to a
//!     noun-based name (as opposed, for instance, to
//!     "equality_comparable"), consistently with the general naming
//!     style of Breath C++ components.
//!
template< typename T >
class equality_comparison
{
    friend bool         operator==( T const & lhs, T const & rhs)
    {
        return lhs.is_equal( rhs );
    }
    friend bool         operator!=( T const & lhs, T const & rhs )
    {
        return !( lhs == rhs ) ;
    }

protected:
                        ~equality_comparison() noexcept = default ;
} ;

}

using breath::adl_shield::
                        equality_comparison ;
}


#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
