// =========================================================================
//                    Copyright 2008-2015 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "tool/include_guard/macro_name.hpp"
#include "breath/diagnostics/exception.hpp"
#include "breath/process/program_status.hpp"

#include <cstdio> // for EOF
#include <iostream>
#include <istream>
#include <ostream>
#include <string>

int
main( int argc, char * argv[] )
{
    using               breath::program_status ;

    try {

        program_status::instance().parse_command_line( argc, argv/*, "include_guard"*/ ) ;
        std::string const   prefix = "BREATH_GUARD_" ;
        int const           random_part_length = 32 ;

        macro_name_creation::exit_status
                            status ;
        std::string const   name =
            ::make_macro_name( prefix, random_part_length, &status ) ;

        if ( status == macro_name_creation::could_not_release_entropy_source ) {
            std::cerr << "Unable to release the entropy source." << std::endl ;
            program_status::instance().declare_error(
                                            program_status::comment ) ;
        }

        std::cout << "#ifndef " << name   << std::endl
                  << "#define " << name   << std::endl    ;
        if (std::cin.peek() != EOF ){
            std::cout << std::cin.rdbuf() << std::endl    ;
        }
        std::cout << "#endif"             << std::endl    ;

    } catch (std::exception const & ex ) {
        std::cerr << ex.what() << std::endl ;
        program_status::instance().declare_error( program_status::error ) ;
    } catch ( ... ) {
        program_status::instance().declare_error( program_status::fatal ) ;
    }
    return program_status::instance().exit_status() ;

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
