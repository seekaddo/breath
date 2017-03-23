// =========================================================================
//                    Copyright 2007-2015 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________
//
//!     \file
//!     \brief A description of the operating system.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_vUmfBUe7uRgM2lw3OI5BLE0BSMMDnzDS
#define BREATH_GUARD_vUmfBUe7uRgM2lw3OI5BLE0BSMMDnzDS

#include "breath/diagnostics/exception.hpp"
#include <iosfwd>
#include <string>

namespace breath {

class operating_system_name
{
} ;

class operating_system_name_error
    : public exception
{
public:
    explicit            operating_system_name_error( std::string const & ) noexcept ;
    virtual char const *
                        what() const noexcept override ;
private:
    enum { what_string_max_size = 256 } ;
    char                m_what_str[ what_string_max_size ];
} ;

std::ostream &      operator <<( std::ostream &, operating_system_name const & ) ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
