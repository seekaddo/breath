// =========================================================================
//                    Copyright 2006-2007 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#ifndef BREATH_GUARD_zosglTB4b62CILKxpxWmmQwQ28EfOH6T
#define BREATH_GUARD_zosglTB4b62CILKxpxWmmQwQ28EfOH6T

/*! \file
    \brief
        Compile-time checker for complete types.

        Instantiation renders the program ill-formed if \a T is not a complete
        type.
*/

namespace breath {

//      check_type_completeness()
//
//
//!     To be used to check that \c T is a complete type at the
//!     point of instantiation. If \c T is incomplete then the
//!     expression
//!     \code
//!         check_type_completeness< T >()
//!     \endcode
//!     renders the program \e ill-formed.
// -----------------------------------------------------------------------
template< typename T >
void
check_type_completeness()
{
    static_cast< void >( sizeof( T ) ) ;
}

}

#endif
// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
