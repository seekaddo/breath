#include <string.h>
#include <cerrno>
#include <ostream>

namespace breath {


last_api_error::last_api_error() noexcept
    : m_errno( errno )
{
    int const           ret = strerror_r( m_errno,
                                          &m_message[ 0 ],
                                          sizeof m_message - 1 ) ;
    if ( ret != 0 ) {
        strcpy( &m_message[ 0 ], "strerror_r failed: see error code") ;
    }
}

last_api_error::last_api_error( last_api_error const & other ) noexcept
    :   m_errno( other.m_errno )
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
operator<<( std::ostream & dest, last_api_error const & last)
{
    return dest << last.m_message << "[code: " << last.code() << "]" ;
}

}
