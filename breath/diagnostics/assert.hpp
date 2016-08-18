// =========================================================================
//                    Copyright 2006-2010 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#ifndef BREATH_GUARD_k8gjtzbloTDgF7FRM6AWORSGsE1IHkXq
#define BREATH_GUARD_k8gjtzbloTDgF7FRM6AWORSGsE1IHkXq

/*
        A basic assertion facility

        BREATH_ASSERT is the simplest runtime assertion facility in the Breath
        collection. Differently from the standard assert() it is always
        defined and has always the same expansion (regardless of NDEBUG).

    Rationale:
        It has become "common practice" to define the macro NDEBUG
        when compiling the "release" version of code. Many IDEs do so
        silently. In fact, "NDEBUG" (or a logical complement of it, such as
        _DEBUG) has become the macro which is usually checked for, via if, by
        your library code to know which version of it (release/debug) you want
        to link with. We believe, though, that assertions must be left on in
        the release version of the product. So we wanted an assert macro
        decoupled from NDEBUG. (Thinking of it, there has been a fatal
        misunderstanding: the C committee thought of a macro to enable/disable
        assertions, but alas named it "NDEBUG", which suggests "no debug". And
        that's the meaning everyone seems to have assigned to it. Had they
        called it e.g. "NASSERT" all this wouldn't probably have happened.)
*/

namespace breath {
namespace assert_private {

void fire( char const * message,
           char const * file_name,
           unsigned long line_number ) noexcept ;

}
}



//      BREATH_ASSERT:
//      --------------
//
//      The code
//
//          BREATH_ASSERT( expression)
//
//      expands to an expression. The statement
//
//          BREATH_ASSERT( expression) ;
//
//      has the following effect:
//
//      first, if expression is not implicitly convertible to
//      bool the program is ill-formed; otherwise, when the statement
//      is executed, an assertion is triggered \e iif the result of
//      such a conversion is \c false.
// 
//      In this context, "triggering an assertion" means writing
//      information related to the specific macro invocation (e.g.
//      line number and source file name) to \c std::cerr, then
//      calling std::abort().
// 
//      The behavior of BREATH_ASSERT isn't conditioned by any macro
//      (differently from the standard assert, whose definition is
//      conditioned by NDEBUG).
// 
// ---------------------------------------------------------------------------
#define BREATH_ASSERT( expression )                                          \
    (                                                                        \
        ( expression )                                                       \
          ? static_cast< void >( 0 )                                         \
          : breath::assert_private::fire( #expression, __FILE__, __LINE__ )  \
    )                                                                     /**/


#endif
// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
