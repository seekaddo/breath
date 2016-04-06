// =========================================================================
//                    Copyright 2007-2008 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/algorithm/secure_fill.hpp"
#include <algorithm>


namespace breath {

template< typename T, std::size_t n >
void
sensitive_buffer< T[ n ] >::wipe()
{
    breeze::secure_fill( m_data ) ;
}

template< typename T, std::size_t n >
sensitive_buffer< T[ n ] >::sensitive_buffer()
{
    // Calling secure_fill() might cause too much performance loss; and
    // then we are not supposed to cleanup data left over by others.
    // But until measurement...
    wipe() ;
}

template< typename T, std::size_t n >
template< typename InputIter >
sensitive_buffer< T[ n ] >::sensitive_buffer( InputIter begin,
                                              InputIter end )
{
    std::copy( begin, end, this->begin() ) ;
}

template< typename T, std::size_t n >
sensitive_buffer< T[ n ] >::sensitive_buffer( T const ( &src )[ n ] )
{
    std::copy( src, src + n, this->begin() ) ;
}

template< typename T, std::size_t n >
sensitive_buffer< T[ n ] >::~sensitive_buffer()
{
    wipe() ;
}

template< typename T, std::size_t n >
typename sensitive_buffer< T[ n ] >::iterator
sensitive_buffer< T[ n ] >::begin()
{
    return m_data ;
}

template< typename T, std::size_t n >
typename sensitive_buffer< T[ n ] >::iterator
sensitive_buffer< T[ n ] >::end()
{
    return m_data + n ;
}

template< typename T, std::size_t n >
typename sensitive_buffer< T[ n ] >::const_iterator
sensitive_buffer< T[ n ] >::begin() const
{
    return m_data ;
}

template< typename T, std::size_t n >
typename sensitive_buffer< T[ n ] >::const_iterator
sensitive_buffer< T[ n ] >::end() const
{
    return m_data + n ;
}

template< typename T, std::size_t n >
typename sensitive_buffer< T[ n ] >::reference
sensitive_buffer< T[ n ] >::operator[]( size_type index )
{
    return m_data[ index ] ;
}

template< typename T, std::size_t n >
typename sensitive_buffer< T[ n ] >::const_reference
sensitive_buffer< T[ n ] >::operator[]( size_type index ) const
{
    return m_data[ index ] ;
}

}
// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
