// =========================================================================
//                       Copyright 2007 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________
//
//!     \file
//!     \brief Operating system platform.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_aXJLfITxDVHm5WGYsFVUsk2fosp8rU04
#define BREATH_GUARD_aXJLfITxDVHm5WGYsFVUsk2fosp8rU04

#include "breath/operator/equality_comparison.hpp"

namespace breath {

class os_platform
    : private equality_comparison< os_platform >
{
private:
    friend class windows_version_info;
    typedef int value_type;
    value_type m_id;

private:
    explicit os_platform( value_type v );

public:
    bool is_equal( const os_platform & ) const;

    static const os_platform
            windows_nt,
            windows_9x,
            win32s
            ;
} ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
