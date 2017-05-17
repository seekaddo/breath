// =========================================================================
//                       Copyright 2017 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________
//
//      Implementation of readable_type_name() for gcc.
// -------------------------------------------------------------------------

#include "breath/diagnostics/exception.hpp"

#include <cstdlib>
#include <cxxabi.h>
#include <typeinfo>

namespace breath {

template< typename T >
std::string
readable_type_name()
{
    int                 status ;
    char * const        p = abi::__cxa_demangle( typeid( T ).name(),
                                                 nullptr,
                                                 0,
                                                 &status ) ;
    if ( status != 0 ) {
        throw breath::exception( "__cxa_demangle() failed" ) ;
    }

    std::string         ret ;

    try {
        ret = p ;
    } catch ( ... ) {
        std::free( p ) ;
        throw ;
    }

    std::free( p ) ;
    return ret ;

}

template<>
std::string
readable_type_name< std::string >()
{
    return "string" ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
