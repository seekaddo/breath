// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________
//
//!     \file
//!     \brief The primary MAC address.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_JaU2rvd68IroPxPXXroTc2bew3AipiVP
#define BREATH_GUARD_JaU2rvd68IroPxPXXroTc2bew3AipiVP

#include "breath/idiom/declare_non_copyable.hpp"
#include <cinttypes>
#include <array>
#include <ostream>

namespace breath {

class node_id
{
public:
    //!     Copy constructor and copy-assignment operator deleted.
    // ---------------------------------------------------------------------
    BREATH_DECLARE_NON_COPYABLE( node_id )

                        node_id() ;
    //!     \return The one and only instance of \c node_id.
    // ---------------------------------------------------------------------
    static node_id const &
                        instance() ;
    //!     \return The \c n-th byte of the MAC address.
    // ---------------------------------------------------------------------
    uint8_t             operator[]( int n ) const ;

private:
    std::array< uint8_t, 6 >
                        m_address ; // MAC Address

    //!     Outputs a textual representation of \c id to the stream
    //!     \c s.
    // -----------------------------------------------------------------------
    friend std::ostream & operator <<( std::ostream & s, node_id const & id ) ;
} ;


}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
