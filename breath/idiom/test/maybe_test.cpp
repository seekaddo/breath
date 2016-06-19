// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/idiom/maybe.hpp"
#include "breath/testing/testing.hpp"
#include <string>
#include <iostream>
#include <utility>

void
check_constructors()
{
    using breath::maybe;

    // default constructor
    {
        maybe< int >    m ;
        BREATH_CHECK( ! m.is_valid() ) ;
    }
    
    // ordinary constructor
    {
        std::string const   s( "Hello" ) ;
        maybe< std::string >
                            m( s ) ;
        BREATH_CHECK( m.is_valid() && m.value() == "Hello" ) ;
    }

    // copy constructor
    {
        maybe< std::string > invalid ;
        maybe< std::string > m( invalid ) ;
        BREATH_CHECK( ! m.is_valid() ) ;

        maybe< std::string > valid( "foo" ) ;
        maybe< std::string > m2( valid) ;

        BREATH_CHECK( m2.is_valid() && m2.value() == "foo" ) ;
    }

    // move constructor
    {
        std::string         s = "Hello" ;
        maybe< std::string > m( s ) ;
        maybe< std::string > m2 = std::move( m ) ;
        BREATH_CHECK( m2.is_valid() && m2.value() == "Hello" ) ;
    }

    // constructor from T &&
    {
        maybe< std::string > m( "Hello" ) ; // from temporary
        BREATH_CHECK( m.is_valid() && m.value() == "Hello" ) ;
    }
}

void
check_assignments()
{
    using breath::maybe ;

    // copy assignment operator
    {
        maybe< int >        m ;
        maybe< int >        invalid ;
        maybe< int >        valid( 1 ) ;
        m = invalid ;
        BREATH_CHECK( ! m.is_valid() ) ;
        m = valid ;
        BREATH_CHECK( m.is_valid() && m.value() == 1 ) ;
        m = invalid ;
        BREATH_CHECK( ! m.is_valid() ) ;
        m = valid ;
        m = valid ;
        BREATH_CHECK( m.is_valid() && m.value() == 1 ) ;
    }

    // operator=( T const & )
    {
        std::string          s = "Hello" ;
        std::string          t = "world" ;
        maybe< std::string > m ;
        m = s ;
        BREATH_CHECK( m.is_valid() && m.value() == "Hello" ) ;
        m = t ;
        BREATH_CHECK( m.is_valid() && m.value() == "world" ) ;
    }

    // move assignment operator
    {
        maybe< std::string > m ;
        maybe< std::string > m2 ;
        maybe< std::string > m3( "Ciao" ) ;
        m = std::move( m2 ) ; // invalid -> invalid
        BREATH_CHECK( ! m.is_valid() ) ;
        m = std::move( m3 ) ; // valid -> invalid
        BREATH_CHECK( m.is_valid() && m.value() == "Ciao" ) ;
        maybe< std::string > m4 ;
        m = std::move( m4 ) ; // invalid -> valid
        BREATH_CHECK( ! m.is_valid() ) ;
        maybe< std::string > m5( "mondo" ) ;
        maybe< std::string > m6( "!" ) ;
        m = m5 ;
        m = std::move( m6 ) ; // valid -> valid
        BREATH_CHECK( m.is_valid() && m.value() == "!" ) ;
    }

    // operator =( T && )
    {
        maybe< std::string > m ;
        m = "Hello" ; // from temporary
        BREATH_CHECK( m.is_valid() && m.value() == "Hello" ) ;
        m = "world" ;
        BREATH_CHECK( m.is_valid() && m.value() == "world" ) ;
    }
}

int
main()
{
    using namespace breath;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    test_runner::instance().run( { check_constructors, check_assignments } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
