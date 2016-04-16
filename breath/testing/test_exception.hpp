// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#ifndef BREATH_GUARD_8msuVkqs5IBc3s7j1mDOtGC97uqTUGg0
#define BREATH_GUARD_8msuVkqs5IBc3s7j1mDOtGC97uqTUGg0

#include "breath/diagnostics/exception.hpp"
#include <ostream>

namespace breath {

class test_exception : public exception
{
public:
                        test_exception( char const * filename,
                                        unsigned long line ) noexcept ;
                        test_exception( std::string const &,
                                        char const * filename,
                                        unsigned long line ) noexcept ;
    char const *        filename() const noexcept ;
    unsigned long       line()     const noexcept ;

private:
    char const *        m_filename;
    unsigned long       m_line ;
} ;

std::ostream &      operator <<(std::ostream & os, test_exception const &) ;











}



#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
