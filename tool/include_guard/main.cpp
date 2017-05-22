// =========================================================================
//                    Copyright 2008-2015 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "tool/include_guard/macro_name.hpp"
#include "breath/diagnostics/exception.hpp"
#include "breath/process/program.hpp"

#include <cstdio> // for EOF
#include <iostream>
#include <istream>
#include <ostream>
#include <string>

int
main( int argc, char * argv[] )
{
    using               breath::program ;

    try {
        program::instance().parse_command_line( argc, argv/*, "include_guard"*/ ) ;
        std::string const   prefix = "BREATH_GUARD_" ;
        int const           random_part_length = 32 ;

        macro_name_creation::exit_status
                            status ;
        std::string const   name =
            ::make_macro_name( prefix, random_part_length, &status ) ;

        if ( status == macro_name_creation::could_not_release_entropy_source ) {
            std::cerr << "Unable to release the entropy source." << std::endl ;
            program::instance().declare_error( program::comment ) ;
        }

        std::cout << "#ifndef " << name   << std::endl
                  << "#define " << name   << std::endl    ;
        if ( std::cin.peek() != EOF ){
            std::cout << std::cin.rdbuf() << std::endl    ;
        }
        std::cout << "#endif"             << std::endl    ;

    } catch (std::exception const & ex ) {
        std::cerr << ex.what() << std::endl ;
        program::instance().declare_error( program::error ) ;
    } catch ( ... ) {
        program::instance().declare_error( program::fatal ) ;
    }
    return program::instance().exit_code() ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
