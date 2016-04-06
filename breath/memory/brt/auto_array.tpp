// =========================================================================
//                       Copyright 2006 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________


#include "breath/diagnostics/check_type_completeness.hpp"

namespace breath {

template< typename T >
auto_array< T >::auto_array()
    :   m_ptr( nullptr )
{
}

template< typename T >
auto_array< T >::auto_array( T * p )
    :   m_ptr( p )
{
}

template< typename T >
auto_array< T >::~auto_array()
{
    do_delete() ;
}

template< typename T >
T *
auto_array< T >::get()
{
    return m_ptr ;
}

template< typename T >
void
auto_array< T >::reset( T * p )
{
    if ( p == m_ptr ) {
        return ;
    }
    do_delete() ;
    m_ptr = p ;
}

template< typename T >
void
auto_array< T >::do_delete()
{
    check_type_completeness< T >() ;
    delete[] m_ptr;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
