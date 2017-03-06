// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________
//
//!     \file
//!     \brief An object to report unit tests errors to a \c
//!            std::ostream.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_XgKxFi9sRq7YDgySOH2206PWX2ZxQrtB
#define BREATH_GUARD_XgKxFi9sRq7YDgySOH2206PWX2ZxQrtB

#include "breath/testing/test_reporter.hpp"
#include <cstddef>
#include <iosfwd>

namespace breath {

class console_reporter : public test_reporter
{
public:
    explicit            console_reporter( std::ostream & os ) ;

    virtual void        on_all_tests_begin() override ;
    virtual void        on_all_tests_end() override ;
    virtual void        on_test_begin( std::size_t test_number, char const * name = "" ) override ;
    virtual void        on_test_passed( std::size_t test_number ) override ;
    virtual void        on_test_failed( std::size_t test_number, test_exception const & ) override ;
    virtual void        on_unexpected_exception( std::size_t test_number ) override ;
    virtual void        on_unexpected_exception( std::size_t test_number, std::exception const & ) override ;
private:
    std::ostream &      m_stream ;
    unsigned            m_passed ;
    unsigned            m_failed ;
    unsigned            m_unexpected_exceptions ;
} ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
