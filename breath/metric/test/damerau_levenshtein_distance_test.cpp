// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2017 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/metric/damerau_levenshtein_distance.hpp"
#include "breath/testing/check.hpp"
#include "breath/testing/console_reporter.hpp"
#include "breath/testing/test_runner.hpp"
#include <cstddef>
#include <iostream>
#include <string>

int                 test_damerau_levenshtein_distance() ;

namespace {

void
single_check( std::string const & first, std::string const & second,
              std::ptrdiff_t distance )
{
    BREATH_CHECK( breath::damerau_levenshtein_distance( first, second )
                                                                == distance ) ;
    BREATH_CHECK( breath::damerau_levenshtein_distance( second, first )
                                                                == distance ) ;
}

void
check()
{
    single_check( "", "", 0 ) ;
    single_check( "foo", "", 3 ) ;
    single_check( "hello", "hello", 0 ) ;
    single_check( "hello", "hallo", 1 ) ;
    single_check( "sitting", "kitten", 3 ) ;
    single_check( "spell", "spel", 1 ) ;
    single_check( "suggest", "suggets", 1 ) ;
    single_check( "wikipedia", "encyclopedia", 7 ) ;
    single_check( "abcde", "acbed", 2 ) ;
    single_check( "abcde", "baced", 2 ) ;
    single_check( "abcde", "baecd", 3 ) ;
    single_check( "Smith", "Stitch", 2 ) ;
}

}

int
test_damerau_levenshtein_distance()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run( "damerau_levenshtein_distance()",
                                        { check } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
