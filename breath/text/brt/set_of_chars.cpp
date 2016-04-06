// =========================================================================
//                       Copyright 2008 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/text/set_of_chars.hpp"

#include <algorithm>
#include <climits> // gps could use our meta::stuff, or C++11 numeric_limits
#include <cstddef>
#include <deque>

namespace breath {

set_of_chars::set_of_chars()
    :   m_bits( set_of_chars::size )
{
}

// gps note that this contructor cannot add a '\0'; to do that
// you must use the overload taking an std::string.
set_of_chars::set_of_chars( char const * elements )
    : m_bits( set_of_chars::size )
{
    add( elements ) ;
}

set_of_chars::set_of_chars( std::string const & s )
    : m_bits( set_of_chars::size )
{
    add( s ) ;
}

set_of_chars::set_of_chars( except_for, char c )
    :   m_bits( set_of_chars::size, true)
{
    remove( c ) ;
}

set_of_chars::set_of_chars( except_for, char const * s )
    :   m_bits( set_of_chars::size, true)
{
    remove( s ) ;
}

set_of_chars::set_of_chars( except_for, std::string const & s )
    :   m_bits( set_of_chars::size, true)
{
    remove( s ) ;
}

set_of_chars::~set_of_chars()
{
}

set_of_chars::set_of_chars( set_of_chars const & other )
    : m_bits( other.m_bits )
{

}

set_of_chars &
set_of_chars::operator=( set_of_chars const & other )
{
    m_bits = other.m_bits ;
    return *this ;
}

bool
set_of_chars::operator==( set_of_chars const & other ) const
{
    return m_bits == other.m_bits ;
}

bool
set_of_chars::contains( char c ) const
{
    return m_bits[ c - CHAR_MIN ] ; //gps duplication!
}

set_of_chars &
set_of_chars::add( char c )
{
    m_bits[ c - CHAR_MIN ] = true ;
    return *this ;
}

set_of_chars &
set_of_chars::add( char const * s )
{
    while ( *s != '\0' ) {
        add( *s ) ;
        ++ s ;
    }
    return *this ;
}

set_of_chars &
set_of_chars::add( std::string const & s )
{
    for( auto curr = s.begin() ; curr != s.end() ; ++ curr ) {
        add( *curr ) ;
    }
    return *this ;
}

set_of_chars &
set_of_chars::remove( char c )
{
    m_bits[ c - CHAR_MIN ] = false ;
    return *this ;
}

set_of_chars &
set_of_chars::remove( char const * s )
{
    while ( *s != '\0' ) {
        remove( *s ) ;
        ++ s ;
    }
    return *this ;
}

set_of_chars &
set_of_chars::remove( std::string const & s )
{
    for ( auto curr = s.begin() ; curr != s.end() ; ++ curr ) {
        remove( *curr ) ;
    }
    return *this ;
}

void
set_of_chars::complement()
{
    for ( auto it = m_bits.begin(); it != m_bits.end() ; ++ it ) {
        *it = ! *it ;
    }
}

std::string
set_of_chars::as_string() const
{
    return std::string( begin(), end() ) ;
}

// note: in C++14 we could forward to std::count() [std, 25.2.9][gps]
std::size_t
set_of_chars::count() const
{
    std::size_t         counter = 0 ;
    for( auto curr = m_bits.begin() ; curr != m_bits.end(); ++ curr ) {
        if ( *curr ) {
            ++ counter ;
        }
    }
    return counter ;
}

bool
set_of_chars::is_empty() const
{
    for( auto curr = m_bits.begin() ; curr != m_bits.end() ; ++ curr ) {
        if ( *curr ) {
            return false ;
        }
    }

    return true ;
}

//      iterators:
// ---------------------------------------------------------------------------
set_of_chars::iterator::iterator()
    : m_owner( nullptr ),
      m_index( infinity )
    
{
}

set_of_chars::iterator::iterator( set_of_chars const & sc )
    : m_owner( &sc.m_bits ),
      m_index( 0 )
{
     ++ *this ;
}

set_of_chars::iterator
set_of_chars::begin() const
{
    return iterator( *this ) ;
}

set_of_chars::iterator
set_of_chars::end() const
{
    return iterator() ;
}

char
set_of_chars::iterator::operator * () const
{
    return static_cast< char >( m_index - CHAR_MIN ) ;
}

set_of_chars::iterator &
set_of_chars::iterator::operator ++()
{
    ++m_index ;
    while( m_index < infinity && ! (*m_owner)[m_index] ) {
        ++ m_index ;
    }

    return *this ;
}

set_of_chars::iterator
set_of_chars::iterator::operator ++( int )
{
    auto                    tmp( *this );
    operator ++();
    return tmp ;
}

bool
set_of_chars::iterator::operator ==( iterator const & other ) const
{
    // gps note: it's UB to compare iterators into different containers [OK?]
    return m_index == other.m_index ;
}

bool
set_of_chars::iterator::operator !=( iterator const & other ) const
{
    return ! ( *this == other ) ;
}


}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
