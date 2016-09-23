// =========================================================================
//                       Copyright 2006 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________
//
//!     \file
//!     \brief A macro to prevent expansion of other macros.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_KezEcitYEJtdq09HtWJssCKDNm4sXaV5
#define BREATH_GUARD_KezEcitYEJtdq09HtWJssCKDNm4sXaV5

//!     The only purpose of this macro is to prevent the expansion of the
//!     preceding identifier, in case it is defined as a function-like macro.
//!     Any macro would do (in fact, anything which isn't an open paren), but
//!     this has a self-documenting name.
//!
//!     Typically used for the identifiers min and max. Example:
//!
//!     <code>
//!         int const           m =
//!         std::numeric_limits< int >::max BREATH_PREVENT_MACRO_EXPANSION () ;
//!     </code>
//!
//!     Note that you can prevent macro substitution by enclosing the offending
//!     name in parentheses, but that also inhibits ADL, whereas this macro has
//!     absolutely no effect in that regard.

#define BREATH_PREVENT_MACRO_EXPANSION

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
