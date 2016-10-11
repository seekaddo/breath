// =========================================================================
//                       Copyright 2015 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/diagnostics/exception.hpp"
#include <iosfwd>

namespace breath {

class last_api_error
    :   public exception
{
public:
                        last_api_error() noexcept ;
                        last_api_error( char const * ) noexcept ;
                        last_api_error( last_api_error const & other ) noexcept ;
                        ~last_api_error() noexcept ;
    int                 code() const noexcept ;
    char const *        what() const noexcept ;
private:


    void                operator=( last_api_error const & ) ; // not defined

    friend std::ostream &
                        operator<<( std::ostream &, last_api_error const & ) ;

    int                 m_errno ;
    char                m_message[ 64 * 1024 ] ;
} ;

}
// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
