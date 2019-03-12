// =========================================================================
//                    Copyright 2010-2019 Gennaro Prota
//                     Copyright 1997-2003 James Kanze
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________
//
//!     \file
//!     \brief A singleton class to manage the overall program status.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_1kA1ToNG1qsz9KwlXD9MfVvhaHxMym5b
#define BREATH_GUARD_1kA1ToNG1qsz9KwlXD9MfVvhaHxMym5b

#include "breath/idiom/declare_non_copyable.hpp"
#include "breath/idiom/maybe.hpp"
#include "breath/process/exit_code.hpp"
#include <string>

namespace breath {

class program
{
public:
    BREATH_DECLARE_NON_COPYABLE( program )

private:
                        program() noexcept ;
                        ~program() noexcept = default ;

public:
    //!     The gravity of an error.
    //
    //      NOTE: keep the enumeration in sync with the exit_codes[]
    //            array in the implementation file.
    // ----------------------------------------------------------------------
    enum gravity
    {
        comment = 0, // equivalent to success
        warning,
        error,
        fatal,
        internal
    } ;

    static program &    instance() noexcept ;

    //!     \return
    //!         An integer to be passed to \c std::exit() or returned
    //!         from \c main(). This corresponds to the most severe
    //!         error reported by client code to the \c program class
    //!         through the \c declare_error() member function.
    //!
    //!     If the system supports it, the various gravities will be
    //!     distinguished in the exit code; if not, all you get is
    //!     \c EXIT_SUCCESS or \c EXIT_FAILURE.
    //!
    //!     Important: this function also flushes \c std::cout, and
    //!     calls \c declare_error() if the flush fails. For this
    //!     reason, it is not const.
    // ----------------------------------------------------------------------
    int                 exit_code() ;

    //!     Sets the program name from the arguments to main, if they
    //!     contain a non-empty name (<tt>argc > 0 && argv[ 0 ][ 0 ] !=
    //!     '\0'</tt>). Otherwise does nothing.
    //!
    //!     If the name is set, any leading path is stripped.
    //!
    //!     Precondition: name was not set before.
    //!
    //!     Postcondition: none.
    // ----------------------------------------------------------------------
    void                set_name( int argc, char const * const * argv ) ;

    //!     Sets the program name from the arguments to main, if they
    //!     contain a non-empty name; otherwise sets it from \c fallback.
    //!
    //!     In any case, any leading path is stripped.
    //!
    //!     Precondition: <tt>! fallback.empty()</tt> and name was not
    //!     set before.
    //!
    //!     Postcondition: <tt>name().is_valid()</tt>.
    // ----------------------------------------------------------------------
    void                set_name( int argc, char const * const * argv,
                                  std::string const & fallback ) ;

    //!     Sets the program name to \c name, with any leading path
    //!     stripped.
    //!
    //!     Precondition: <tt>! name.empty()</tt> and name was not set
    //!     before.
    //!
    //!     Postcondition: <tt>name().is_valid()</tt>.
    // ----------------------------------------------------------------------
    void                set_name( std::string const & name ) ;

    //!     \return The program name set by \c set_name().
    // ----------------------------------------------------------------------
    maybe< std::string >
                        name() const ;

    //!     Declares a program error.
    //!
    //!     \param g
    //!         The gravity of the error. If the gravity is higher
    //!         than any seen previously, it is saved to be used in
    //!         \c exit_code().
    // ----------------------------------------------------------------------
    void                declare_error( gravity g ) ;

private:
    void                do_set_name( std::string const & name ) ;

    gravity             m_max_gravity ;
    maybe< std::string >
                        m_program_name ;
} ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
