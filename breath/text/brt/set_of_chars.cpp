// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2008 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/text/set_of_chars.hpp"

#include <climits> // gps could use our meta::stuff, or C++11 numeric_limits
#include <cstddef>

namespace breath {

int
set_of_chars::to_index( char c ) noexcept
{
    return c - CHAR_MIN ;
}

set_of_chars::set_of_chars() noexcept
    :   m_bits()
{
}

set_of_chars::set_of_chars( char const * elements ) noexcept
    : m_bits()
{
    add( elements ) ;
}

set_of_chars::set_of_chars( std::string const & s ) noexcept
    : m_bits()
{
    add( s ) ;
}

set_of_chars::set_of_chars( except_for, char c ) noexcept
    :   m_bits()
{
    m_bits.flip() ;
    remove( c ) ;
}

set_of_chars::set_of_chars( except_for, char const * s ) noexcept
    :   m_bits()
{
    m_bits.flip() ;
    remove( s ) ;
}

set_of_chars::set_of_chars( except_for, std::string const & s ) noexcept
    :   m_bits()
{
    m_bits.flip() ;
    remove( s ) ;
}

set_of_chars::~set_of_chars() noexcept
{
}

set_of_chars::set_of_chars( set_of_chars const & other ) noexcept
    : m_bits( other.m_bits )
{

}

set_of_chars &
set_of_chars::operator =( set_of_chars const & other ) noexcept
{
    m_bits = other.m_bits ;
    return *this ;
}

bool
set_of_chars::operator ==( set_of_chars const & other ) const noexcept
{
    return m_bits == other.m_bits ;
}

bool
set_of_chars::contains( char c ) const noexcept
{
    return m_bits[ to_index( c ) ] ;
}

set_of_chars &
set_of_chars::add( char c ) noexcept
{
    m_bits.set( to_index( c ) ) ;
    return *this ;
}

set_of_chars &
set_of_chars::add( char const * s ) noexcept
{
    while ( *s != '\0' ) {
        add( *s ) ;
        ++ s ;
    }
    return *this ;
}

set_of_chars &
set_of_chars::add( std::string const & s ) noexcept
{
    for( auto curr = s.cbegin() ; curr != s.cend() ; ++ curr ) {
        add( *curr ) ;
    }
    return *this ;
}

set_of_chars &
set_of_chars::remove( char c ) noexcept
{
    m_bits.reset( to_index( c ) ) ;
    return *this ;
}

set_of_chars &
set_of_chars::remove( char const * s ) noexcept
{
    while ( *s != '\0' ) {
        remove( *s ) ;
        ++ s ;
    }
    return *this ;
}

set_of_chars &
set_of_chars::remove( std::string const & s ) noexcept
{
    for ( auto curr = s.cbegin() ; curr != s.cend() ; ++ curr ) {
        remove( *curr ) ;
    }
    return *this ;
}

void
set_of_chars::complement() noexcept
{
    m_bits.flip() ;
}

std::string
set_of_chars::as_string() const
{
    return std::string( cbegin(), cend() ) ;
}

std::size_t
set_of_chars::count() const noexcept
{
    return m_bits.count() ;
}

bool
set_of_chars::is_empty() const noexcept
{
    return m_bits.none() ;
}

//      iterators:
// ---------------------------------------------------------------------------
set_of_chars::iterator::iterator() noexcept
    : m_owner( nullptr ),
      m_index( size )

{
}

set_of_chars::iterator::iterator( set_of_chars const & sc ) noexcept
    : m_owner( &sc.m_bits ),
      m_index( -1 )
{
     ++ *this ;
}

set_of_chars::iterator
set_of_chars::begin() const noexcept
{
    return iterator( *this ) ;
}

set_of_chars::iterator
set_of_chars::end() const noexcept
{
    return iterator() ;
}

set_of_chars::const_iterator
set_of_chars::cbegin() const noexcept
{
    return begin() ;
}

set_of_chars::const_iterator
set_of_chars::cend() const noexcept
{
    return end() ;
}

char
set_of_chars::iterator::operator * () const noexcept
{
    return static_cast< char >( m_index - CHAR_MIN ) ;
}

set_of_chars::iterator &
set_of_chars::iterator::operator ++() noexcept
{
    do {
        ++ m_index ;
    } while ( m_index < size && ! ( *m_owner )[ m_index ] ) ;

    return *this ;
}

set_of_chars::iterator
set_of_chars::iterator::operator ++( int ) noexcept
{
    auto                    tmp( *this ) ;
    operator ++() ;
    return tmp ;
}

bool
set_of_chars::iterator::operator ==( iterator const & other ) const noexcept
{
    //      Note that it's UB to compare iterators into different
    //      owners.
    // -----------------------------------------------------------------------
    return m_index == other.m_index ;
}

bool
set_of_chars::iterator::operator !=( iterator const & other ) const noexcept
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
