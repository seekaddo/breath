// =========================================================================
//                    Copyright 2006-2018 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/diagnostics/assert.hpp"
#include <new>
#include <utility>

namespace breath {

template< typename T >
maybe< T >::maybe() noexcept
    :   m_buffer()
{
}

template< typename T >
maybe< T >::maybe( maybe const & source )
{
    if ( source.is_valid() ) {
        construct( source.value() ) ;
        m_is_valid = true ;
    }
}

template< typename T >
maybe< T >::maybe( T const & t )
{
    construct( t ) ;
    m_is_valid = true ;
}

template< typename T >
maybe< T >::maybe( T && t )
{
    construct( std::move( t ) ) ;
    m_is_valid = true ;
}

template< typename T >
maybe< T >::maybe( maybe && source )
{
    if ( source.is_valid() ) {
        construct( std::move( source.non_const_value() ) ) ;
        m_is_valid = true ;
    }
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
maybe< T >::operator =( maybe< T > const & other )
{
    if ( other.is_valid() ) {
        if ( is_valid() ) {
            *static_cast< T * >( m_buffer.address() ) = other.value() ;
        } else {
            construct( other.value() ) ;
            m_is_valid = true ;
        }
    } else if ( is_valid() ) {
        destroy() ;
        m_is_valid = false ;
    }
    return *this ;
}

template< typename T >
maybe< T > &
maybe< T >::operator =( maybe && other )
{
    if ( other.is_valid() ) {
        if ( is_valid() ) {
            *static_cast< T * >( m_buffer.address() )
                                       = std::move( other.non_const_value() ) ;
        } else {
            construct( std::move( other.non_const_value() ) ) ;
            m_is_valid = true ;
        }
    } else if ( is_valid() ) {
        destroy() ;
        m_is_valid = false ;
    }
    return *this ;
}

//      Note that T's assignment operator exception guarantee reflects
//      that of this operator =().
// ---------------------------------------------------------------------
template< typename T >
maybe< T > &
maybe< T >::operator =( T const & rhs )
{
    if ( is_valid() ) {
        *static_cast< T * >( m_buffer.address() ) = rhs ;
        // m_is_valid = true ;
    } else {
        construct( rhs ) ;
    }
    m_is_valid = true ;
    return *this ;
}

template< typename T >
maybe< T > &
maybe< T >::operator =( T && t )
{
    if ( is_valid() ) {
        *static_cast< T * >( m_buffer.address() ) = std::move( t ) ;
    } else {
        construct( std::move( t ) ) ;
    }
    m_is_valid = true ;
    return *this ;
}

template< typename T >
bool
maybe< T >::is_valid() const noexcept
{
    return m_is_valid ;
}

template< typename T >
T const &
maybe< T >::value() const noexcept
{
    BREATH_ASSERT( is_valid() ) ;
    return *static_cast< T const * >( m_buffer.address() ) ;
}

template< typename T >
T
maybe< T >::default_to( T const & t ) const noexcept
{
    return is_valid()
        ? value()
        : t ;
}

template< typename T >
void
maybe< T >::construct( T const & source )
{
    BREATH_ASSERT( ! is_valid() ) ;
    new( m_buffer.address() ) T( source ) ; // may throw
}

template< typename T >
void
maybe< T >::construct( T && source )
{
    BREATH_ASSERT( ! is_valid() ) ;
    new( m_buffer.address() ) T( std::move( source ) ) ; // may throw
}

template< typename T >
void
maybe< T >::destroy() noexcept
{
    BREATH_ASSERT( is_valid() ) ;
    static_cast< T * >( m_buffer.address() )->T::~T() ;
}

template< typename T >
T &
maybe< T >::non_const_value() noexcept
{
    BREATH_ASSERT( is_valid() ) ;
    return *static_cast< T * >( m_buffer.address() ) ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
