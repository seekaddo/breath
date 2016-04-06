// =========================================================================
//                       Copyright 2013 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________


// gps temp
#undef NDEBUG
#include <assert.h>
#define DO_TEST(x)  assert(x)
// ^^^^^^^^ ---------------

#include "breath/debugging/dump_expression.hpp"
#include <iostream>
#include <ostream> // not necessary in C++11
#include <sstream>

int
main()
{
    // TEST 1)
    // TODO TODO
    // io volevo "catturare" l'output di std::cout in uno stringstream,
    // ma non ci sono riuscito. Devo controllare poi nella guida RogueWave (gps
    //  cos'è ora? Apache?).
    //
    // L'idea era di controllare ad es. che 1<<3 esce come 8 e non come "1" seguito
    // da "3"; ed eventualmente altri controlli.
    //

    BREATH_DUMP_EXPRESSION( 1 << 3 ) ;

    // TEST 2)
    // now check with some strings (gps ricordati di portare questo test nei
    // test di BREATH_STRINGIZE (e controllare cosa dice lo standard)!)
    BREATH_DUMP_EXPRESSION( "test" ) ;

    // TEST 3)
    // check that macros are expanded (the replacement lists here are
    // intentionally not parenthesized, although we already have a
    // separate parenthesis-test in place).
#   define OBJECT_LIKE_DUMMY        1 << 3 * 2
#   define FUNCTION_LIKE_DUMMY()    1 << 3 * 4

    BREATH_DUMP_EXPRESSION( OBJECT_LIKE_DUMMY ) ;
    BREATH_DUMP_EXPRESSION( FUNCTION_LIKE_DUMMY() ) ;


    // TEST 4)
    // The one case that the macro doesn't detect: a macro that is object-like
    // and expands to its own name (of course it's not important, but it's good
    // to have a test here, in case I manage to detect it).
    int                             BREATH_dummy = 1 ;
#   define BREATH_dummy             BREATH_dummy

    BREATH_DUMP_EXPRESSION( BREATH_dummy ) ;

}
// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
