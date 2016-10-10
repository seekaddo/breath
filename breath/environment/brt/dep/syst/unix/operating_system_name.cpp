// =========================================================================
//                    Copyright 2007-2015 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/diagnostics/last_api_error.hpp"
#include <cerrno>
#include <ostream>
#include <string.h> // for strncpy
#include <sys/utsname.h>

namespace breath {

operating_system_name_error::operating_system_name_error( std::string const & s ) noexcept
{
    strncpy( m_what_str, s.c_str(), what_string_max_size ) ;
}

char const *
operating_system_name_error::what() const noexcept
{
    return m_what_str ;
}


std::ostream &
operator <<( std::ostream & dest, operating_system_name const &)
{
    utsname             un  ;
    int const           ret = uname( &un ) ;

    if ( ret == -1 ) {
        last_api_error const
                            err ;
        throw breath::operating_system_name_error( err.what() ) ;
    }

    return dest << un.sysname
                << ' ' << un.release
                << ' ' << un.version
                << ' ' << un.machine ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
