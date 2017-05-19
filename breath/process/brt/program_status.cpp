// =========================================================================
//                       Copyright 2010 Gennaro Prota
//                     Copyright 1997-2003 James Kanze
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/process/program_status.hpp"
#include "breath/counting/count.hpp"
#include "breath/diagnostics/assert.hpp"
#include "breath/path/base_filename.hpp"
#include "breath/process/exit_code.hpp"

#include <iostream>
#include <ostream>
#include <string>

namespace breath {

program_status::program_status() noexcept
    :   m_max_gravity( comment )
{
    std::basic_ios< char > *
                        arr[] = {
        &std::cin,
        &std::cout,
        &std::cerr,
        &std::clog
    } ;
    for ( auto stream : arr ) {
        try {
            stream->exceptions( std::ios_base::badbit ) ;
        } catch ( std::ios_base::failure const & ) {
            // nothing to do
        }
    }
}

program_status &
program_status::instance() noexcept
{
    static program_status
                        the_instance ;
    return the_instance ;
}

int
program_status::exit_code() const
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
        instance().declare_error( program_status::internal ) ;
        is_internal = true ;
        std::cerr << "impossible gravity seen in class program_status" ;
    }
    std::cout.flush() ;
    if ( std::cout.fail() ) {
        instance().declare_error( error ) ; // NOTE: we need an error message here -gps
    }
    return is_internal
            ? exit_internal
            : table[ m_max_gravity ] ;
}

void
program_status::parse_command_line( int argc, char const * const *
                                argv, std::string const & program_name )
{
    BREATH_ASSERT( m_program_name.empty() ) ;

    std::string const
                    name = ! program_name.empty()
                                ? program_name
                                : argc > 0
                                        ? argv[ 0 ]
                                        : "<unknown program>"
                                ;
    m_program_name = breath::base_filename( name ) ;
}

std::string
program_status::program_name() const
{
    BREATH_ASSERT( ! m_program_name.empty() ) ;

    return m_program_name ;
}

void
program_status::declare_error( program_status::gravity g ) // gps nome OK?
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
