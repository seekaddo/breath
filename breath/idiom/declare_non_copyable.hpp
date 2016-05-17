// =========================================================================
//                    Copyright 2006-2015 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#ifndef BREATH_GUARD_BssKAsCiqQzBgpiZdcF0pqcl37YyLxoi
#define BREATH_GUARD_BssKAsCiqQzBgpiZdcF0pqcl37YyLxoi

//!     Handy macro to declare a class non-copyable.
//!     It is better invoked in a public section of the class declaration
//!     (gives better error messages).
// ----------------------------------------------------------------------------
#define BREATH_DECLARE_NON_COPYABLE( class_name )                       \
                                                                        \
                        class_name( class_name const & ) = delete ;     \
    void                operator=( class_name const & )  = delete ;     \
                                                                     /**/

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
