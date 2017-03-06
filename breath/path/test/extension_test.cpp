// =========================================================================
//                       Copyright 2006 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________


#include "breath/path/extension.hpp"

///////// gps
#include "breath/diagnostics/assert.hpp"
#define DO_TEST( x ) BREATH_ASSERT( x )
//////

int
main()
{
    using               breath::extension ;

    DO_TEST( extension( "" )      == "" ) ;
    DO_TEST( extension( "my_file" )      == "" ) ;
    DO_TEST( extension( "/my_file.exe" )     == ".exe" ) ;

    DO_TEST( extension( "C:\\Documents and Settings\\Genny\\Desktop\\my_file.bat" )
                                                            == ".bat" ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
