// =========================================================================
//                    Copyright 2006-2015 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________


#include "breath/diagnostics/assert.hpp"

namespace breath {

template< typename T >
maybe< T >::maybe()
    :   m_buffer(),
        m_is_valid( false )
{
}

template< typename T >
maybe< T >::maybe( maybe const & source )
{
    if ( source.is_valid() ) {
        construct( source.value() ) ;
        m_is_valid = true ;
    } else {
        m_is_valid = false ;
    }
}


template< typename T > // gps explicit on the definition?
maybe< T >::maybe( T const & t )
{
    construct( t ) ;
    m_is_valid = true ;
}

template< typename T >
maybe< T >::~maybe() noexcept
{
    if ( is_valid() ) {
        destroy() ;
    }
}

template< typename T >
maybe< T > &
maybe< T >::operator=( T const & rhs ) // gps strong guarantee???
{
    if ( is_valid() ) {
        // Note how we set m_is_valid to false until we are sure
        // that the subsequent operator=() on T does not throw
        m_is_valid = false ;
        *static_cast< T * >( m_buffer.address() ) = rhs ;
        // m_is_valid = true ;
    } else {
        construct( rhs ) ;
    }
    m_is_valid = true ;
    return *this ;
}

template< typename T >
bool
maybe< T >::is_valid() const
{
    return m_is_valid ;
}

template< typename T >
T const &
maybe< T >::value() const
{
    BREATH_ASSERT( is_valid() ) ;
    return *static_cast< T const * >( m_buffer.address() ) ;
}

template< typename T >
T const &
maybe< T >::default_to( T const & t ) const
{
    return is_valid()
        ? value()
        : t ;
}

template< typename T >
void
maybe< T >::construct( T const & source )
{
    :: /*gps OK??? */ new( m_buffer.address() ) T( source ) ; // may throw
}

template< typename T >
void
maybe< T >::destroy()
{
    BREATH_ASSERT( is_valid() ) ;
    static_cast< T * >( m_buffer.address() )->T::~T() ;    // OK????

}

}
// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
