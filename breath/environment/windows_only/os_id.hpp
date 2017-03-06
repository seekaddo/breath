// =========================================================================
//                    Copyright 2007-2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________
//
//!     \file
//!     \brief Operating system identifier.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_y14wSYOBPQ4ReQuQzkBRjijvOvqDhYc7
#define BREATH_GUARD_y14wSYOBPQ4ReQuQzkBRjijvOvqDhYc7

// for Windows OSes

#include "breath/operator/equality_comparison.hpp"
#include <iosfwd>

namespace breath {

//      A thin wrapper around an int: we assign distinct integral
//      numbers to the different Windows versions.
//      ===============================================================
//
// Comparison operators rationale:
//
//   In my first idea of this class, it was my intent to support inequality
//   comparisons:
//
//     // windows 2000 or "later"?
//     if( id >= os_id::windows_2000 )
//
//   But...
//   not only this might not make sense for other systems; at the time of
//   writing (April 2007) Windows versions seem to have an "official" total
//   ordering (see the various requires clauses in the SDK docs), but what
//   about the future? MS seems on the way of "parallelizing" their OS
//   products in a "client line" (Windows XP etc.) and a "server line"
//   (Windows Server 2003 etc.); this makes me think that we could have two
//   future Windows variants of which neither is "higher" or "lower" than
//   the other one
class os_id
    : private equality_comparison< os_id >
{
private:
    typedef int     id_type ;
    id_type         m_id ;

    explicit        os_id( id_type ) ;

    friend std::ostream &
                    operator <<( std::ostream &, os_id const & ) ;

public:
    // compiler-generated copy and destructor

    bool            is_equal( os_id const & ) const ;

    static const os_id
        windows_unknown,

        windows_2000,
        windows_xp,
        windows_server_2003,
        windows_home_server,
        windows_storage_server_2003,
        windows_server_2003_r2,
        windows_xp_professional_x64_edition,
        windows_vista,
        windows_server_2008,
        windows_server_2008_r2,
        windows_7,
        windows_8,
        windows_server_2012,
        windows_8_1,
        windows_server_2012_r2,
        windows_10,
        windows_server_2016
    ;

} ;

// gps controlla se mettiamo una dichiarazione anche prima (vedi crypto/)
std::ostream & operator <<( std::ostream & dest, os_id const & id ) ;
}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
