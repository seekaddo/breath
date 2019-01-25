// =========================================================================
//                       Copyright 2010 Gennaro Prota
//                     Copyright 1997-2003 James Kanze
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/process/program.hpp"
#include "breath/counting/count.hpp"
#include "breath/diagnostics/assert.hpp"
#include "breath/path/base_file_name.hpp"
#include "breath/process/exit_code.hpp"

#include <iostream>
#include <ostream>
#include <string>

namespace breath {

program::program() noexcept
    :   m_max_gravity( comment )
{
}

program &
program::instance() noexcept
{
    static program      the_instance ;

    return the_instance ;
}

int
program::exit_code() const
{
    // NOTE: gps this code is very fragile; how to avoid this dependency?
    // NOTE: keep in sync with the enumeration definition in the .hpp file.
    static int const    table[] = {
        exit_success,
        exit_warning,
        exit_error,
        exit_fatal,
        exit_internal
    } ;

    bool                is_internal = false ;
    if ( static_cast< unsigned int >( m_max_gravity ) >= breath::count( table ) ) {
        instance().declare_error( program::internal ) ;
        is_internal = true ;
        std::cerr << "impossible gravity seen in class program" ;
    }
    std::cout.flush() ;
    if ( std::cout.fail() ) {
        instance().declare_error( program::error ) ; // NOTE: we need an error
                                                     // message here -gps
    }
    return is_internal
            ? exit_internal
            : table[ m_max_gravity ] ;
}

void
program::parse_command_line( int argc, char const * const * argv,
                             std::string const & program_name )
{
    BREATH_ASSERT( m_program_name.empty() ) ;

    std::string const   name = ! program_name.empty()
                                    ? program_name
                                    : ( argc > 0 && argv[ 0 ][ 0 ] != '\0' )
                                        ? argv[ 0 ]
                                        : "<unknown program>"
                                ;
    m_program_name = breath::base_file_name( name ) ;
}

std::string
program::name() const
{
    BREATH_ASSERT( ! m_program_name.empty() ) ;

    return m_program_name ;
}

void
program::declare_error( program::gravity g ) // gps nome OK?
{
    if ( g > m_max_gravity ) {
        m_max_gravity = g ;
    }
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
