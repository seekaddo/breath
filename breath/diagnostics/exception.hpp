// =========================================================================
//                       Copyright 2015 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________


#ifndef BREATH_EXCEPTION_jdfhh54l32lk1
#define BREATH_EXCEPTION_jdfhh54l32lk1

#include <exception>
#include <string>

namespace breath {

class exception : public virtual std::exception
{
public:
    exception() noexcept ;
    exception( std::string const & what_msg ) noexcept ;

    exception( exception const & ) noexcept ; //gps C++11 =default?
    exception & operator=( exception const & ) noexcept ;

    virtual ~exception() noexcept ;

    virtual char const * what() const noexcept ;

private:
    enum { what_message_max_size = 1023 } ;
    char                m_what_message[ what_message_max_size] ;
} ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
