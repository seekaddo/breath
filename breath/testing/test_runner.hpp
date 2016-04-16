// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#ifndef BREATH_GUARD_ljsq7ok4MwSNNxMyfe6xf8RevjbF8jrE
#define BREATH_GUARD_ljsq7ok4MwSNNxMyfe6xf8RevjbF8jrE

#include "breath/idiom/declare_non_copyable.hpp"

namespace breath {

class test_reporter;

class test_runner
{
    BREATH_DECLARE_NON_COPYABLE( test_runner )

private:
                    test_runner() ;

public:
    static test_runner &
                    instance() ;
    void            attach_reporter( test_reporter & ) ;
    template< typename TestDescriptorIterator >
    void            run( TestDescriptorIterator begin, TestDescriptorIterator end ) ;

private:
    test_reporter * m_reporter ;
} ;


template< typename TestDescriptorIterator >
void
test_runner::run( TestDescriptorIterator begin, TestDescriptorIterator end )
{
    std::size_t test_number = 1 ;
    m_reporter->on_all_tests_begin() ;
    for ( ; begin != end ; ++ begin, ++ test_number ) {
        try {
            m_reporter->on_test_begin( test_number ) ;
            (begin->function)() ;
            m_reporter->on_test_passed( test_number );
        } catch ( test_exception const & ) {
            m_reporter->on_test_failed( test_number ) ;
        } catch ( ... ) {
            m_reporter->on_unexpected_exception( test_number ) ;
        }
    }
    m_reporter->on_all_tests_end() ;
}

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
