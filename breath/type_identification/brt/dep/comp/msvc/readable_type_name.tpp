// =========================================================================
//                       Copyright 2017 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________
//
//      Implementation of readable_type_name() for Visual C++.
// -------------------------------------------------------------------------

#include <typeinfo>

namespace breath {

template< typename T >
std::string
readable_type_name()
{
    return typeid( T ).name() ;
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
