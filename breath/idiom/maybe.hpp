// =========================================================================
//                    Copyright 2006-2019 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________
//
//!     \file
//!     \brief A template for "maybe" values.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_93j8pelTutz7YloouImWg9M7REakYYSD
#define BREATH_GUARD_93j8pelTutz7YloouImWg9M7REakYYSD

#include "breath/alignment/aligned_buffer_for.hpp"

namespace breath {

//! \brief
//!     The default traits class for maybe<>. Logically corresponds to
//!     a boolean (valid/invalid).
// --------------------------------------------------------------------------
class boolean_maybe_traits
{
public:
    class status
    {
    public:
        explicit            status( bool b ) noexcept : m_status( b ) {}
        bool                m_status ;
    } ;

    static bool         is_valid( status s ) noexcept
    {
        return s.m_status ;
    }

    static status       default_invalid() noexcept
    {
        return status( false ) ;
    }

    static status       default_valid() noexcept
    {
        return status( true ) ;
    }
} ;



//      maybe< T >:
//      ===========
//
//!     A class template to represent "possible" values. The idea was
//!     signaled by James Kanze in some illo-tempore conversation, and
//!     comes from
//!
//!         John J. Barton, Lee R. Nackman (1994).
//!         Scientific and Engineering C++: An Introduction with
//!         Advanced Techniques and Examples. Addison-Wesley
//!         Professional. ISBN 0-201-53393-6.
//!
//!     which calls it "Fallible".
//!     Basically: \c maybe< T > is used as return type for functions
//!     that logically return a \c T or fail (thus, it is an intrusive,
//!     although lightweight, solution). The \c maybe< T > object
//!     keeps track of its validity state, and any attempt to retrieve
//!     the \c T object when it is marked as invalid will cause an
//!     assertion failure.
//!
//!     Note that the original Barton and Nackman solution threw an
//!     exception, instead.
//!
//!     There are other important differences compared to the version
//!     provided by Barton and Nackman.
//!
//!     1. At least for the moment, there is no \c invalidate()
//!        function; I'm still waiting to see if a reasonable usage for
//!        it exists (perhaps a cache?).
//!
//!     2. No conversion function to \c T is provided. Among other
//!        things, it wouldn't be useful in at least the following
//!        situations:
//!
//!         - when we want to invoke a member function on the "real"
//!           object:
//!
//!             maybe< std::string > my_function() ;
//!             my_function().size() ;        // error
//!             my_function().value().size()  // OK
//!
//!           (but, of course, the latter is stylistically rare: one
//            would usually assign the function return value first)
//!
//!         - when \p T itself has a user defined conversion, which
//!           you want to be applied
//!
//!        As shown above, in these cases you have to explicitly
//!        invoke value().
//!
//!        Curiously enough, B&N's book introduces Fallible<> as an
//!        example of using conversions "to add a binary state" --
//!        valid or invalid-- and checking to objects. The conversion
//!        itself, however, isn't part of the concept: it just makes the
//!        checking more "transparent" (at the well-known cost that
//!        implicit conversions generally bring).
//!
//!     3. It isn't required for T to have a default constructor.
//!
//!     4. Has a richer interface and supports move semantics.
//!
//!     5. Has an additional template parameter (Traits) which allows
//!        specifying several invalid states or several valid states.
//!
//!     The template parameters are:
//!
//!      - T
//
//!        The type of the value to store when the maybe is valid.
//!
//!      - Traits
//
//!        A traits class defining the valid and the invalid states of
//!        the maybe object. It shall contain:
//!
//          - a nested type or typedef named "status" that can be used
//            to store the state of the maybe object
//
//          - an is_valid() static function, which returns whether a
//            given value of type status corresponds to a valid status
//            or not
//
//          - two static functions, named "default_invalid" and
//            "default_valid" which give the default invalid and valid
//            state, respectively
// ---------------------------------------------------------------------------
template< typename T, typename Traits = boolean_maybe_traits >
class maybe
{
public:
    typedef typename Traits::status
                        status_type ;

private:
    aligned_buffer_for< T >
                        m_buffer ;
    status_type         m_status ;

public:
    explicit            maybe( status_type status =
                                          Traits::default_invalid() ) noexcept ;

                        maybe( maybe const & other ) ;

    explicit            maybe( T const & value, status_type status =
                                                     Traits::default_valid() ) ;

                        maybe( maybe && other ) ;
    explicit            maybe( T && value, status_type status =
                                                   Traits::default_valid() ) ;
                        ~maybe() noexcept ;
    maybe &             operator =( maybe const & other ) ;
    maybe &             operator =( T const & value ) ;
    maybe &             operator =( maybe && other ) ;
    maybe &             operator =( T && value ) ;

    status_type         status() const noexcept ;
    bool                is_valid() const noexcept ;

    T const &           value() const noexcept ;

    //!     \returns
    //!     \c value() if \c is_valid(); otherwise \c default_value.
    //!
    //!     Note that, differently from \c value(), this function
    //!     returns by value, which prevents problems of dangling
    //!     references. Note, too, that, for this reason, it is not
    //!     noexcept (T's copy constructor might throw); a conditional
    //!     noexcept() would be an option, but it adds too much
    //!     complexity, in our opinion, and of course we would have to
    //!     use it consistently, not just for default_to().
    // ---------------------------------------------------------------------
    T                   default_to( T const & default_value ) const ;

private:
    void                construct( T && value ) ;
    void                construct( T const & value ) ;
    void                destroy() noexcept ;

    //      used in moving functions only
    //
    T &                 non_const_value() noexcept ;
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
