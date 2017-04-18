// =========================================================================
//                       Copyright 2010 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/process/program_status.hpp"
#include "breath/counting/count.hpp"
#include "breath/path/base_filename.hpp"
#include "breath/process/exit_code.hpp"

#include <iostream>
#include <ostream>
#include <string>

namespace breath {

program_status &
program_status::instance()
{
    static program_status *
                        the_instance = nullptr ;
    if ( the_instance == nullptr ) {
        the_instance = new program_status ;
    }
    return *the_instance ;
}

program_status::program_status()
    :   m_max_gravity() // gps or "success"?
{
    std::cin.exceptions(  std::ios_base::badbit ) ;
    std::cout.exceptions( std::ios_base::badbit ) ;
    std::cerr.exceptions( std::ios_base::badbit ) ;
    std::clog.exceptions( std::ios_base::badbit ) ;
}

program_status::~program_status() noexcept
{
}

// gps controllare poi l'ordine con cui definiamo le member function
int
program_status::exit_status() const
{
    // NOTE: gps this code is very fragile; how to avoid this dependency?
    static int const    table[] = {
        exit_success,
        exit_warning,
        exit_error,
        exit_fatal,
        exit_internal
    } ;

    if ( static_cast<unsigned int>( m_max_gravity ) >= breath::count( table ) ) {
       instance().declare_error( program_status::internal ) ;
       std::cerr << "impossible gravity seen in class program_status" ;
       return exit_status() ;
    }
    std::cout.flush() ;
    return table[ m_max_gravity ] ;
}

void
program_status::parse_command_line( int argc, char const * const *
                                argv, std::string const & program_name )
{
    std::string const
                    name = ! program_name.empty()
                                ? program_name
                                : argc > 0
                                        ? argv[ 0 ]
                                        : "<unknown program>"
                                ;

    m_program_name = breath::base_filename( name ) ;
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
