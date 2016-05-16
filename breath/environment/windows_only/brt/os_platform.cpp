// =========================================================================
//                    Copyright 2007-2015 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________


#include "breath/environment/windows_only/os_platform.hpp"
#include <windows.h>

namespace breath {

os_platform::os_platform( value_type v )
    : m_id( v )
{
}

bool
os_platform::is_equal( const os_platform & other ) const
{
    return m_id == other.m_id;
}

const os_platform
    os_platform::windows_nt( VER_PLATFORM_WIN32_NT ),
    os_platform::windows_9x( VER_PLATFORM_WIN32_WINDOWS ),
    os_platform::win32s(     VER_PLATFORM_WIN32s )
        ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
