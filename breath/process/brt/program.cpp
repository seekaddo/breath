// =========================================================================
//                    Copyright 2010-2019 Gennaro Prota
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
    //
    static int const    table[] = {
        exit_success,
        exit_warning,
        exit_error,
        exit_fatal,
        exit_internal
    } ;

    bool                is_internal = false ;
    if ( static_cast< unsigned int >( m_max_gravity ) >=
                                                     breath::count( table ) ) {
        instance().declare_error( program::internal ) ;
        is_internal = true ;
        std::cerr << "impossible gravity seen in class program" << std::endl ;
    }
    std::cout.flush() ;
    if ( std::cout.fail() ) {
        std::cerr << "I/O error on standard output" << std::endl ;
        instance().declare_error( program::error ) ;
    }
    return is_internal
            ? exit_internal
            : table[ m_max_gravity ] ;
}

void
program::set_name( int argc, char const * const * argv )
{
    BREATH_ASSERT( ! m_program_name.is_valid() ) ;

    if ( argc > 0 && argv[ 0 ][ 0 ] != '\0' ) {
        do_set_name( argv[ 0 ] ) ;
    }
}

void
program::set_name( int argc, char const * const * argv,
                             std::string const & fallback )
{
    BREATH_ASSERT( ! m_program_name.is_valid() ) ;
    BREATH_ASSERT( ! fallback.empty() ) ;

    std::string const     name = ( argc > 0 && argv[ 0 ][ 0 ] != '\0' )
                                    ? argv[ 0 ]
                                    : fallback
                                    ;
    do_set_name( name ) ;
}

void
program::set_name( std::string const & name )
{
    BREATH_ASSERT( ! m_program_name.is_valid() ) ;
    BREATH_ASSERT( ! name.empty() ) ;

    do_set_name( name ) ;
}

maybe< std::string >
program::name() const
{
    return m_program_name ;
}

void
program::declare_error( program::gravity g ) // gps nome OK?
{
    if ( g > m_max_gravity ) {
        m_max_gravity = g ;
    }
}

void
program::do_set_name( std::string const & name )
{
    m_program_name = breath::base_file_name( name ) ;
}


}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
