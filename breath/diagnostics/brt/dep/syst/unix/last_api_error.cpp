// =========================================================================
//                       Copyright 2015 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include <string.h>
#include <cerrno>
#include <ostream>

namespace breath {

char const          strerror_r_failed[] = "strerror_r failed: see error code" ;

last_api_error::last_api_error() noexcept
    : m_errno( errno )
{
    int const           ret = strerror_r( m_errno,
                                          &m_message[ 0 ],
                                          sizeof m_message - 1 ) ;
    if ( ret != 0 ) {
        strcpy( &m_message[ 0 ], strerror_r_failed ) ;
    }
}

last_api_error::last_api_error( char const * p ) noexcept
    : m_errno( errno )
{
    //! \todo
    //! Most of this code is duplicated with the Windows variant.
    //! How to put it in common? --gps
    //
    int const           max_incipit_size = 512 ;
    static_assert( max_incipit_size < ( sizeof m_message / 10 ), "" ) ;

    if ( p != nullptr ) {
        strncpy( m_message, p, max_incipit_size ) ;
    }

    char const          sep[] = ": " ;
    std::size_t const   offset = p == nullptr
                                    ? 0
                                    : strlen( p ) + sizeof sep - 1
                                    ;
    if ( p != nullptr ) {
        strcpy( m_message + (offset - sizeof sep + 1), sep ) ;
    }
    int  const                   ret = strerror_r( m_errno,
                                                   &m_message[ 0 ],
                                                   sizeof m_message - 1 ) ;
    if ( ret != 0 ) {
         strcpy( m_message, strerror_r_failed ) ;
    }

}

last_api_error::last_api_error( last_api_error const & other ) noexcept
    :   exception(), m_errno( other.m_errno )
{
    strcpy( &m_message[ 0 ], &other.m_message[ 0 ] ) ;
}

last_api_error::~last_api_error() noexcept
{
}

int
last_api_error::code() const noexcept
{
    return m_errno ;
}

char const *
last_api_error::what() const noexcept
{
    return m_message ;
}

std::ostream &
operator <<( std::ostream & dest, last_api_error const & last )
{
    return dest << last.m_message << "[code: " << last.code() << "]" ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
