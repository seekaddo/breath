// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#ifndef BREATH_GUARD_JaU2rvd68IroPxPXXroTc2bew3AipiVP
#define BREATH_GUARD_JaU2rvd68IroPxPXXroTc2bew3AipiVP

#include <cinttypes>
#include <array>
#include <ostream>

namespace breath {

class node_id
{
public:
                        node_id() ;
private:
    std::array< uint8_t, 6 >
                        m_address ; // MAC Address

    friend std::ostream & operator <<( std::ostream &, node_id const & ) ;
} ;


}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
