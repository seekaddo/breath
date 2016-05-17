// =========================================================================
//                    Copyright 2006-2015 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#ifndef BREATH_GUARD_93j8pelTutz7YloouImWg9M7REakYYSD
#define BREATH_GUARD_93j8pelTutz7YloouImWg9M7REakYYSD

#include "breath/alignment/aligned_buffer_for.hpp"

namespace breath {

//      maybe< T >:
//      ===========
//
//!     A class template to represent "possible" values. The idea was
//!     signaled by James Kanze in some illo-tempore conversation, and
//!     comes from
//!
//!         John J. Barton, Lee R. Nackman (1994).
//!         Scientific and Engineering C++: An Introduction with
//!         Advanced Techniques and Examples. Addison-Wesley Professional.
//!         ISBN 0-201-53393-6.
//!
//!     which calls it "Fallible".
//!     Basically: \c maybe< T > is used as return type for functions
//!     that logically return a \c T or fail (thus, it is an intrusive,
//!     although lightweight, solution). The \c maybe< T > object
//!     keeps track of its validity state, and any attempt to retrieve
//!     the \c T object when it is marked as invalid will cause an
//!     assertion failure.
//!
//!     Note that the original Barton and Nackman solution did throw
//!     an exception, instead.
//!
//!     There are some important differences compared to the version
//!     provided by Barton and Nackman, many of which can be traced
//!     back to evolution on "best practices" happened after the book
//!     publication.
//!
//!     0. The object can only be validated by providing a \c T: there
//!     is no \c validate() function (and, at least for the moment, no
//!     \c invalidate() either; I'm still waiting to see if a reasonable
//!     usage for it exists).
//!
//!     1. No conversion function to \c T is provided. Among other
//!     things, it wouldn't be useful in at least the following
//!     situations:
//!
//!      - when using a Fallible instance as argument to a function
//!        template:
//!
//!          gps add std::cout << example
//!
//!      - when we want to invoke a member function on the "real" object:
//!
//!          maybe< std::string > my_function();
//!          my_function().size();        // error
//!          my_function().value().size() // OK
//! 
//!        (but, of course, the latter is stylistically rare: one would
//!        usually assign the function return value first)
//!
//!      - when \p T itself has a user defined conversion, which you
//!        want to be applied:
//!
//!          // gps add example
//!
//!
//!     As shown above, in these cases you have to explicitly invoke
//!     value().
//!
//!     Curiously enough, B&N's book introduces Fallible<> as an example
//!     of using conversions "to add a binary state" --valid or invalid--
//!     and checking to objects. The conversion itself, however, isn't
//!     part of the concept: it just makes the checking more
//!     "transparent" (at the well-known cost that implicit conversions
//!     generally bring).
// ---------------------------------------------------------------------------
template< typename T >
class maybe
{
private:
    aligned_buffer_for< T >
                        m_buffer ;
    bool                m_is_valid ;

public:

                        maybe() noexcept ; // POST: ! is_valid()
                        maybe( maybe const & ) ;
    explicit            maybe( T const & ) ;
                        ~maybe() noexcept ;
    maybe &             operator=( maybe const & ) ;
    maybe &             operator=( T const & ) ;

    bool                is_valid() const noexcept ;

    T const &           value() const noexcept ;
    T const &           default_to( T const & t ) const noexcept ;

private:
    void                construct( T const & source ) ;
    void                destroy() noexcept ;
} ;

}

#include "brt/maybe.tpp"
#endif
// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
