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
#include <string>
#include <typeinfo>

namespace breath {

template< typename T >
std::string
readable_type_name()
{
    class deallocator
    {
    public:
        explicit deallocator( char * p )
            : m_p( p )
        {
        }
        ~deallocator()
        {
            std::free( m_p ) ;
        }
    private:
        char * const    m_p ;
    } ;

    int                 status ;
    char const * const  name = typeid( T ).name() ;

    //  For the documentation of __cxa_demangle(), see:
    //    <https://itanium-cxx-abi.github.io/cxx-abi/abi.html>
    // -------------------------------------------------------------------------
    char * const        p = abi::__cxa_demangle( name,
                                                 nullptr,
                                                 nullptr,
                                                 &status ) ;
    if ( status != 0 ) {
        throw breath::exception( "__cxa_demangle() failed to demangle \"" +
                                 std::string( name ) + "\"" ) ;
    }

    deallocator const   dlc( p ) ;

    return std::string( p ) ;
}

template<>
inline std::string
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
