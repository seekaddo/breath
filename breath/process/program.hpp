// =========================================================================
//                    Copyright 2010-2011 Gennaro Prota
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
    // NOTE: keep the enumeration in sync with the array definition in
    //       program::exit_code().
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

    //!     Returns an integer suitable for calling \c std::exit() or
    //!     returning from \c main().
    //!     This corresponds to the "worst" error reported by client
    //!     code to the \c program class through the \c
    //!     declare_error() member function.
    //!
    //!     If the system supports it, the various gravities will be
    //!     distinguished in the return code; if not, all you get is
    //!     \c EXIT_SUCCESS or \c EXIT_FAILURE.
    //!
    //!     Important: this function also flushes \c std::cout, and
    //!     calls \c declare_error() if the flush fails.
    // ----------------------------------------------------------------------
    int                 exit_code() const ;

    //!     Sets the program name from the \c program_name argument or
    //!     from the arguments to main. It must be called at most once
    //!     in the program execution. The advice is to call it in the
    //!     first lines of \c main(), before threading starts.
    //!
    //!     If a non-empty \c program_name is supplied, it takes
    //!     precedence over the arguments to \c main (in that case you
    //!     can also pass \c 0 and \c nullptr for the \c argc and \c
    //!     argv parameters, respectively). In any case, only the
    //!     basename part of the program name is considered.
    // ----------------------------------------------------------------------
    void                set_name( int argc, char const * const *
                                argv, std::string const & program_name = "" ) ;

    //!     \return The program name set by \c set_name().
    //!     An assertion is triggered if \c set_name() had not been
    //!     called before.
    // ----------------------------------------------------------------------
    std::string         name() const ;

    //!     Declares a program error.
    // ----------------------------------------------------------------------
    void                declare_error( gravity g ) ;

private:
     gravity            m_max_gravity ;
     std::string        m_program_name ;
} ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
