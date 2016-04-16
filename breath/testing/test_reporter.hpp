// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#ifndef BREATH_GUARD_I2oO3QRDodQiGPSBaYNHr4wsSe5AloUX
#define BREATH_GUARD_I2oO3QRDodQiGPSBaYNHr4wsSe5AloUX

namespace breath {

class test_reporter
{
public:
    virtual void        on_all_tests_begin() = 0 ;
    virtual void        on_all_tests_end()   = 0 ;
    virtual void        on_test_begin( int test_number, char const * name = "" ) = 0 ;
    virtual void        on_test_passed( int test_number ) = 0 ;
    virtual void        on_test_failed( int test_number ) = 0 ;
    virtual void        on_unexpected_exception( int test_number ) = 0 ;

    virtual             ~test_reporter() {}
} ;

}



#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
