// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#ifndef BREATH_GUARD_I2oO3QRDodQiGPSBaYNHr4wsSe5AloUX
#define BREATH_GUARD_I2oO3QRDodQiGPSBaYNHr4wsSe5AloUX

#include <cstddef>

namespace breath {

class test_exception ;

class test_reporter
{
public:
    virtual void        on_all_tests_begin() = 0 ;
    virtual void        on_all_tests_end()   = 0 ;
    virtual void        on_test_begin( std::size_t test_number, char const * name = "" ) = 0 ;
    virtual void        on_test_passed( std::size_t test_number ) = 0 ;
    virtual void        on_test_failed( std::size_t test_number, test_exception const & ) = 0 ;
    virtual void        on_unexpected_exception( std::size_t test_number ) = 0 ;

    virtual             ~test_reporter() noexcept {}
} ;

}



#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
