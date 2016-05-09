// =========================================================================
//                       Copyright 2008 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________
//
//      Implementation for systems that have /dev/random (Unix)
// -------------------------------------------------------------------------

#include "breath/random/entropy_source.hpp"
#include "breath/diagnostics/assert.hpp"
#include "breath/random/subrange_max.hpp"
#include "breath/idiom/declare_non_copyable.hpp"

#include <cstddef>
#include <cerrno>
#include <limits>
#include <string.h> // for POSIX' strerror
#include <vector>

// -----------------------------------------------------------------------
#include <stdio.h> // temp, and Unix only gps



namespace breath {

class entropy_source::impl
{
    BREATH_DECLARE_NON_COPYABLE( impl )
    
public:
                        impl() ;
                        ~impl() noexcept ;
    bool                release() noexcept ;
    unsigned char /*gps*/
                        next() ;
    result_type
                        minimum() noexcept ;
    result_type
                        maximum() noexcept ;

private:
    bool                is_open() const noexcept ;
    void                to_buffer( unsigned char /*gps*/ * buffer, std::size_t count ) noexcept ;

private:
    FILE *              m_file ;
} ;

entropy_source::impl::impl()
    : m_file( ::fopen( "/dev/random", "rb" ) )
{
    if ( ! is_open() ) {
        entropy_source::exception::raise( "cannot open /dev/random" ) ;
    }


    // Attempt to turn off the library-level buffering. If that fails
    // we ignore the failure.
    //
    // (If the need arises to verify this, I might store the information
    // given by setvbuf's return value and add an is_buffered() member
    // function.)
    // -----------------------------------------------------------------
    ::setvbuf( m_file, nullptr, _IONBF, 0 ) ;
}

entropy_source::impl::~impl() noexcept
{
    release() ;
}


unsigned char //gps
entropy_source::impl::next()
{
    BREATH_ASSERT( is_open() ) ;


    std::vector< unsigned char >
                        buffer( 1 ) ; ///gps OK? {}?
    to_buffer( &buffer[ 0 ], buffer.size() ) ;
    return buffer[ 0 ] ;
}

entropy_source::result_type
entropy_source::impl::minimum() noexcept
{
    return 0 ;
}

entropy_source::result_type
entropy_source::impl::maximum() noexcept
{
    return 255 ;
}

bool
entropy_source::impl::is_open() const noexcept
{
    return m_file != nullptr ;
}

void
entropy_source::impl::to_buffer( unsigned char /*gps*/ * buffer, std::size_t count ) noexcept
{
    auto const          read =
        ::fread( buffer, sizeof buffer[ 0 ], count, m_file ) ;

    if ( read < count ) {
        exception::raise( "not enough bytes" ) ;
    }

}

bool
entropy_source::impl::release() noexcept
{
    // Close is attempted ONCE. Postcondition: is_open() == false, regardless

    bool            success = false ;
    if ( is_open() ) {
        success = ::fclose( m_file ) == 0 ;
        m_file = nullptr ;
    }
    return success ;
}

void
entropy_source::exception::raise( std::string const & message )
{
    throw entropy_source::exception( "Breath entropy_source: "
                                        + message + " - "
                                        + strerror( errno )
                                        ) ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
