// =========================================================================
//                       Copyright 2015 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________
//
//!     \file
//!     \brief Represents a <code>char const</code> * or \c std::string
//!            function argument.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_SCVOL7tEoh41fMb4HRZ21yR1tALwho7n
#define BREATH_GUARD_SCVOL7tEoh41fMb4HRZ21yR1tALwho7n

#include <string>

namespace breath {

class string_argument
{
public:
    //!     Constructs a <code>string_argument</code> from a <code>
    //!     std::string</code>. Intentionally not <code>explicit</code>.
    // -------------------------------------------------------------------------
                        string_argument( std::string const & ) ;

    //!     Constructs a <code>string_argument</code> from a <code>char const
    //!     *</code>. Intentionally not <code>explicit</code>. Asserts if
    //!     the argument equals <code>nullptr</code>.
    // -------------------------------------------------------------------------
                        string_argument( char const * ) ;

    //!     Returns the value in this <code>string_argument</code> as a <code>
    //!     std::string</code>.
    // -------------------------------------------------------------------------
    std::string         value() const ;

private:
    std::string         m_value ;
} ;

}
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
