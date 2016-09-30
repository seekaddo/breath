// =========================================================================
//                       Copyright 2015 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________
//
//!     \file
//!     \brief Base class for all Breath's exceptions.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_11RKjChIvO8xKP1XEZcLxvq7vDyKvcUr
#define BREATH_GUARD_11RKjChIvO8xKP1XEZcLxvq7vDyKvcUr

#include <exception>
#include <string>

namespace breath {

//      exception:
//      ----------
//
//!     Base class for all Breath's exception types. Derives virtually
//!     from std::exception.
// -------------------------------------------------------------------------
class exception : public virtual std::exception
{
public:
    //!     Constructs an object giving a default what() message.
    // ---------------------------------------------------------------------
    exception() noexcept ;

    //!     Constructs an object whose what() function returns a
    //!     pointer to a string equal to what_msg, possibly
    //!     truncated.
    // ---------------------------------------------------------------------    
    exception( std::string const & what_msg ) noexcept ;

    //!     Compiler-generated copy constructor.
    // ---------------------------------------------------------------------
    exception( exception const & ) noexcept = default ;

    //!     Compiler-generated copy-assignment operator.
    // ---------------------------------------------------------------------
    exception & operator=( exception const & ) noexcept = default ;

    //!     Compiler-generated destructor
    // ---------------------------------------------------------------------
    virtual ~exception() noexcept = default ;

    //!     Returns a description of the exception object.
    // ---------------------------------------------------------------------
    virtual char const * what() const noexcept ;

private:
    enum { what_message_max_size = 1023 } ;
    char                m_what_message[ what_message_max_size] ;
} ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
