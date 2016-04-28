// =========================================================================
//                       Copyright 2008 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

// Implementation for systems that have /dev/random (Unix)


#include "breath/diagnostics/assert.hpp"
#include "breath/random/subrange_max.hpp"   // gps OK????
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
    BREATH_DECLARE_NON_COPYABLE( impl ) ;
    
public:
                        impl() ;
                        ~impl() noexcept ;
    bool                release() noexcept ;
    unsigned char /*gps*/
                        next() ;
    result_type         minimum() ;
    result_type         maximum() ;

private:
    bool                is_open() const ;
    void                to_buffer( unsigned char /*gps*/ * buffer, std::size_t count ) ;

private:
    FILE *              m_file ;
} ;

entropy_source::impl::impl()
    : m_file( ::fopen( "/dev/random", "rb" ) )
{
    if ( ! is_open() ) {
        throw 1 ;
    }


    // Attempt to turn off the library-level buffering. If that fails... --gps
    //
    // (If the need arises to verify this, I might store the information given by setvbuf's return value and
    // add an is_buffered() member function.)
    //
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

#if 0  // -------------------------------------------------------------------------------------------
// [0..cap[  OK? gps
//
unsigned char /*gps*/ next( unsigned int cap /*not inclusive OK?*/ )
{
    BREATH_ASSERT( cap > 0 ) ; // OK? or return 0?

    auto                n( next() ) ;
    while ( n > breath::subrange_max( cap-1, entropy_source::max() ) ) {
        n = next() ;     // document complexity gps
    }
    return n ;
}

#endif // -----------------------------------------------------------------------------------------------------------


entropy_source::result_type
minimum()
{
    return 0 ;
}

entropy_source::result_type
maximum()
{
    return 255 ;
}

bool
entropy_source::impl::is_open() const
{
    return m_file != nullptr ;
}

void
entropy_source::impl::to_buffer( unsigned char /*gps*/ * buffer, std::size_t count )
{
    auto const          read =
        ::fread( buffer, sizeof buffer[ 0 ], count, m_file ) ;

    if ( read < count ) {
        exception::raise( "not enough bytes" ) ;
    }

}

bool
entropy_source::impl::release() throw()
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
