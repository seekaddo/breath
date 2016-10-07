// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#ifndef BREATH_GUARD_R3D9wTLwfq8uQKxez4dTpXq0jrHzBXkC
#define BREATH_GUARD_R3D9wTLwfq8uQKxez4dTpXq0jrHzBXkC

#include <string>

namespace breath {

class test_descriptor
{
public:
    //! Constructs the descriptor for a test having a given \c name
    //! and running the given function.
    //! Intentionally not explicit to allow our typical usage:
    //! <code>
    //!     test_runner::instance().run( { func1, func2... funcN } ) ;
    //! </code>
    // -----------------------------------------------------------------------
                        test_descriptor( void( & )(), char const * name = "" ) noexcept ;
    typedef      void( &test_function )() ;

public:
    test_function       function() const noexcept ;
    std::string         name() const noexcept ;
private:
    test_function       m_function ;
    std::string         m_name ;
} ;


}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
