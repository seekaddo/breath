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
    ///static int const    success = 0 ; // gps
    BREATH_DECLARE_NON_COPYABLE( program_status )

private:
                        program_status() ;
                        ~program_status() noexcept = default ;

#if 0
    // Rationale for the pimpl idiom:
    //
    // I didn't want to introduce a physical dependency on our fallible<> from
    // this include file (and fallible<> is handy for instance to manage the
    // absence of program name). The first iteration of this class just used
    // a supplementary bool data member, which in all honesty...
    //
    class               impl ;
    impl *              m_impl ;
#endif

public:
    enum gravity
    {
        comment = 0, // equivalent to success
        warning,
        error,
        fatal,
        internal
    } ;


    static program_status &
                        instance() ;

    // Returns an integer suitable for calling exit() --gps
    // This is the "worst" error reported by user code to the program_status
    // singleton. gps CONTROLLA QUESTO... in realta noi ora riportiamo un enum
    //
    // 0 == OK; the greater, the worse
    //
    int                 exit_status() const ;

    // This is useful to "extract" the program name (if any) from the arguments
    // to main(). It must be called at most once in the program execution. The
    // advice is to call it in the first lines of main(), before threading
    // starts.
    //
    void                parse_command_line( int argc, char const * const *
                                argv, std::string const & program_name = "" ) ;
    void                declare_error( gravity g ) ;


    //      set_warning(), set_fatal(), etc.:
    //      ---------------------------------
    //
    //      Each of these functions returns a reference to
    //      std::cerr [gps OK? or clog?], so that
    //      the caller can "chain", and format, the corresponding error
    //      message.
    //
    //      The message is output immediately; the error status is
    //      updated.
    //
    //
    //
    //      Example:
    //
    //        set_fatal() << "an error occurred." << std::endl ;
    //
    //      Usually the program is exited, with a
    //
    //        return program_status...::exit_status() ;
    //
    //      from main(), but this is not the only possible case
    //

    //std::ostream &      warning() ;
    //std::ostream &      error() ;
    //std::ostream &      fatal() ;

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
