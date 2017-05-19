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

#include "breath/process/exit_code.hpp"
#include "breath/idiom/declare_non_copyable.hpp"
#include <string>

namespace breath {

class program_status
{
public:
    BREATH_DECLARE_NON_COPYABLE( program_status )

private:
                        program_status() noexcept ;
                        ~program_status() noexcept = default ;

public:
    // NOTE: keep the enumeration in sync with the array definition in
    //       program_status::exit_status().
    // ----------------------------------------------------------------------
    enum gravity
    {
        comment = 0, // equivalent to success
        warning,
        error,
        fatal,
        internal
    } ;

    static program_status &
                        instance() noexcept ;

    //!     Returns an integer suitable for calling \c std::exit() or
    //!     returning from \c main().
    //!     This corresponds to the "worst" error reported by client
    //!     code to the \c program_status singleton.
    //!
    //!     If the system supports it, the various gravities will be
    //!     distinguished in the return code; if not, all you get is
    //!     \c EXIT_SUCCESS or \c EXIT_FAILURE.
    //!
    //!     Important: this function also flushes \c std::cout, and
    //!     generates an error if the flush fails.
    // ----------------------------------------------------------------------
    int                 exit_code() const ;

    //!     This is useful to "extract" the program name (if any) from
    //!     the arguments to \c main(). It must be called at most once
    //!     in the program execution. The advice is to call it in the
    //!     first lines of \c main(), before threading starts.
    //!
    //!     If a non-empty \c program_name is supplied, it takes
    //!     precedence over the arguments to \c main. Only the
    //!     basename part of the program name is considered.
    // ----------------------------------------------------------------------
    void                parse_command_line( int argc, char const * const *
                                argv, std::string const & program_name = "" ) ;

    //!     \return The program name set by \c parse_command_line().
    //!     An assertion is triggered if \c parse_command_line() had
    //!     not been called before.
    // ----------------------------------------------------------------------
    std::string         program_name() const ;

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
