// =========================================================================
//                       Copyright 2015 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#ifndef BREATH_GUARD_0IbzhpmeQvdgWhXSSEDKYfNu88kSfPsS
#define BREATH_GUARD_0IbzhpmeQvdgWhXSSEDKYfNu88kSfPsS

#include "breath/idiom/declare_non_copyable.hpp"
#include <Windows.h>

namespace breath {
namespace process_private {

class handle
{
    BREATH_DECLARE_NON_COPYABLE( handle )

public:
    explicit            handle( HANDLE h) : m_handle( h )
                        {}
                        ~handle() noexcept
                        {
                            if ( m_handle != NULL ) {
                                CloseHandle( m_handle ) ;
                            }
                        }
    HANDLE              get() const
                        {
                            return m_handle ;
                        }
private:
    HANDLE              m_handle ;
} ;

}
}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
