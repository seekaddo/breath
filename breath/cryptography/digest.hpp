// ===========================================================================
//                     Copyright 2006-2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Cryptographic hash digest object.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_HJb5zsPZzS9ztbt5GdVJMPv00mZUAnQI
#define BREATH_GUARD_HJb5zsPZzS9ztbt5GdVJMPv00mZUAnQI

#include "breath/operator/equality_comparison.hpp"
#include <iosfwd>

namespace breath {

//      digest:
//      =======
//
//!     A digest object represents the result of applying a digest
//!     algorithm to a given input sequence.
// ---------------------------------------------------------------------------
template< typename Hasher >
class digest
    :   private equality_comparison< digest< Hasher > >
{
public:
    typedef typename Hasher::byte_type const *
                        const_iterator ;

    //!\name Initialization
    //!\{
    //!     Constructs a digest from a Hasher. Since the \c Hasher
    //!     argument is passed by value its state is not affected.
    // -----------------------------------------------------------------------
    explicit            digest( Hasher hasher_copy ) ;
    //!\}

    //!     Copy and destruction.
    //!     Compiler-generated copy constructor, copy assignment
    //!     operator and destructor.
    // -----------------------------------------------------------------------


    //!     Equality comparison (both \c == and \c != are provided).
    // -----------------------------------------------------------------------
    bool                is_equal( digest< Hasher > const & ) const ;

    //!     \name Byte-based iteration (read-only)
    //!           const_iterator is a forward iterator - gps
    //!     \{
    const_iterator      begin() const ;
    const_iterator      end() const ;
    //!     \}

    //      less:
    //      =====
    //
    //!     Implements a strict weak ordering relation between digests
    //!     (from the same Hasher type). Useful for ordered associative
    //!     containers.
    //!
    //!     The function call operator is not \c noexcept, and the class
    //!     is a \c friend, because I'd like this part of the library,
    //!     which is the oldest, to be still compilable as C++03, if
    //!     needed.
    // -----------------------------------------------------------------------
    class               less ;
    friend class        less ;
    class               less
    {
    public:
        bool                operator()( digest< Hasher > const & d1,
                                        digest< Hasher > const & d2 ) const ;
    } ;

private:
    typename Hasher::raw_digest_type
                        m_raw_digest ;
} ;

//!     Outputs a hexadecimal representation of the digest. The case of
//!     the letters A-F is unspecified (this allows us to support e.g.
//!     \c std::uppercase and \c std::nouppercase in the future). But
//!     it's guaranteed that all letters will have the same case.
// ---------------------------------------------------------------------------
template< typename Hasher >
std::ostream &      operator <<( std::ostream           & os,
                                 digest< Hasher > const & d ) ;

//      make_digest():
//      ==============
//
//!     Convenience function (can use type deduction).
//!
//!     \return
//!         digest< Hasher >( h )
// ---------------------------------------------------------------------------
template< typename Hasher >
digest< Hasher >    make_digest( Hasher const & h ) ;

}

#include "brt/digest.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
