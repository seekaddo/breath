// ===========================================================================
//                        Copyright 2013 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A set of chars.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_Gq4RCdDZQAIMmQBL7I3lbPfT3oHjV7of
#define BREATH_GUARD_Gq4RCdDZQAIMmQBL7I3lbPfT3oHjV7of

#include "breath/top_level_namespace.hpp"
#include <bitset>
#include <climits> // avoid the verbosity of numeric_limits
#include <cstddef>
#include <iterator>
#include <string>

namespace breath_ns {

//      set_of_chars:
//      =============
//
//!     A set of chars.
//!
//!     With respect to a \c std::string, a \c set_of_chars can't have
//!     duplicates and may model the concept more closely; and it has
//!     different complexity guarantees: adding a char, removing a char,
//!     and testing if a char is in the set are all O(1); on the other
//!     hand, incrementing an iterator is a linear search.
//!
//!     Note that several functions, below, are overloaded on \c char
//!     and <code>char const *</code>. Now, depending on whether plain
//!     \c char has a sign, CHAR_MIN may expand to a (non-char) null
//!     pointer constant, which means that e.g. the call to add() in
//!
//!     <code>
//!         set_of_chars sc ;
//!         sc.add( CHAR_MIN ) ;
//!     </code>
//!
//!     may be ambiguous. To avoid the ambiguity, write:
//!
//!     <code>
//!         sc.add( static_cast< char >( CHAR_MIN ) ) ;
//!     </code>
//!
//!     or use
//!
//!     <code>
//!         std::numeric_limits< char >::min()
//!     </code>
// ---------------------------------------------------------------------------
class set_of_chars
{
public:
    //!     Constructs an empty set.
    //!
    //!     \post
    //!         is_empty()
    // -----------------------------------------------------------------------
                        set_of_chars() noexcept ;

    //!     Constructs a set containing all and only the non-null
    //!     elements of the string pointed to by \c s.
    //!
    //!     \pre
    //!         s != nullptr
    // -----------------------------------------------------------------------
    explicit            set_of_chars( char const * s ) noexcept ;

    //!     Constructs a set containing all and only the characters in
    //!     \c s (including null characters, if any).
    // -----------------------------------------------------------------------
    explicit            set_of_chars( std::string const & s ) noexcept ;

    //!     Constructs a set containing all and only the characters in
    //!     the range <code>[begin, end)</code>.
    // -----------------------------------------------------------------------
    template< typename FwdIterator>
                        set_of_chars( FwdIterator begin, FwdIterator end )
                                                                      noexcept ;

    //!     A special value used by some constructors.
    // -----------------------------------------------------------------------
    enum except_for { except } ;

    //!     Constructs a set containing all characters except \c c.
    // -----------------------------------------------------------------------
                        set_of_chars( except_for, char c ) noexcept ;

    //!     Constructs a set containing all characters except the
    //!     non-null characters in the string pointed to by \c s.
    //!
    //!     \pre
    //!         s != nullptr
    // -----------------------------------------------------------------------
                        set_of_chars( except_for, char const * s ) noexcept ;

    //!     Constructs a set containing all characters except those in
    //!     \c s.
    // -----------------------------------------------------------------------
                        set_of_chars( except_for, std::string const & s )
                                                                      noexcept ;

    //!     Constructs a copy of \c other.
    //!
    //!     \post
    //!         *this == other
    // -----------------------------------------------------------------------
                        set_of_chars( set_of_chars const & other ) noexcept ;

    //!     Copy-assigns from \c other.
    //!
    //!     \post
    //!         *this == other
    //!
    //!     \note
    //!         All iterators into \c *this are invalidated.
    // -----------------------------------------------------------------------
    set_of_chars &      operator =( set_of_chars const & other ) noexcept ;

    //!     Destroys the set.
    //!
    //!     \note
    //!         All iterators into \c *this are invalidated.
    // -----------------------------------------------------------------------
                        ~set_of_chars() noexcept ;

    //!     Compares \c *this and \c other.
    //!
    //!     \return
    //!         \c true if and only if the two sets contain the same
    //!         characters.
    // -----------------------------------------------------------------------
    bool                operator ==( set_of_chars const & other ) const
                                                                      noexcept ;

    //!     \return
    //!         \c true if an only if \c *this contains the character
    //!         \c c.
    // -----------------------------------------------------------------------
    bool                contains( char c ) const noexcept ;

    //!     Adds the character \c c to the set.
    //!
    //!     \note
    //!         No iterators are invalidated.
    // -----------------------------------------------------------------------
    set_of_chars &      add( char c ) noexcept ;

    //!     Adds all the non-null characters in the string pointed to by
    //!     \c s to the set.
    //!
    //!     \pre
    //!         s != nullptr
    //!
    //!     \note
    //!         No iterators are invalidated.
    // -----------------------------------------------------------------------
    set_of_chars &      add( char const * s ) noexcept ;

    //!     Adds all the characters in \c s to the set.
    //!
    //!     \note
    //!         No iterators are invalidated.
    // -----------------------------------------------------------------------
    set_of_chars &      add( std::string const & s ) noexcept ;

    //!     Adds all the characters in the range <code>[begin, end)
    //!     </code> to the set.
    //!
    //!     \note
    //!         No iterators are invalidated.
    // -----------------------------------------------------------------------
    template< typename FwdIterator >
    set_of_chars &      add( FwdIterator begin, FwdIterator end ) noexcept ;

    //!     Removes the character \c c from the set.
    //!
    //!     \note
    //!         All iterators referring to \c c are invalidated.
    // -----------------------------------------------------------------------
    set_of_chars &      remove( char c ) noexcept ;

    //!     Removes all the non-null characters in the string pointed to
    //!     by \c s from the set.
    //!
    //!     \pre
    //!         s != nullptr
    //!
    //!     \note
    //!         All iterators referring to removed characters are
    //!         invalidated.
    // -----------------------------------------------------------------------
    set_of_chars &      remove( char const * s ) noexcept ;

    //!     Removes all the characters in \c s from the set.
    //!
    //!     \note
    //!         All iterators referring to removed characters are
    //!         invalidated.
    // -----------------------------------------------------------------------
    set_of_chars &      remove( std::string const & s ) noexcept ;

    //!     Mutates the set into its complement.
    //!
    //!     \note
    //!         All iterators into \c *this are invalidated.
    // -----------------------------------------------------------------------
    void                complement() noexcept ;

    //!     \return
    //!         A string with all and only the characters contained in
    //!         the set.
    // -----------------------------------------------------------------------
    std::string         as_string() const ;

    //!     \return
    //!         The cardinality of the set.
    // -----------------------------------------------------------------------
    std::ptrdiff_t      count() const noexcept ;

    //!     \return
    //!         Whether the set contains no characters.
    // -----------------------------------------------------------------------
    bool                is_empty() const noexcept ;


    class               iterator ;
    friend class        iterator ;
    typedef iterator    const_iterator ;

    //!\{   Read-only iterators for the standard library.
    // -----------------------------------------------------------------------
    iterator            begin() const noexcept ;
    iterator            end() const noexcept ;

    const_iterator      cbegin() const noexcept ;
    const_iterator      cend() const noexcept ;
    //!\}

private:
    enum { size = CHAR_MAX - CHAR_MIN + 1 } ;
    typedef std::bitset< size >
                        bits_type ;
    typedef int         index_type ;
    bits_type           m_bits ;

    static index_type   to_index( char c ) noexcept ;
    static char         to_char( index_type index ) noexcept ;

public:
    //      iterator:
    //      =========
    //
    //!     An iterator for the set.
    //!
    //!     Iterates over all of the characters in the set.  It is a
    //!     \e constant forward iterator (\c iterator and \c
    //!     const_iterator have the same semantics).
    // -----------------------------------------------------------------------
    class               iterator
    {
    public:
        //!\{   Typedefs for the standard library.
        // -------------------------------------------------------------------
        typedef std::forward_iterator_tag
                            iterator_category  ;
        typedef char        value_type         ;
        typedef int         difference_type    ;
        typedef char const *pointer            ;
        typedef char const &reference          ;
        //!\}

        //!     Constructs a one-past-the-end iterator.
        // -------------------------------------------------------------------
                            iterator() noexcept ;

        //!     Constructs an iterator to the first character in \c sc.
        // -------------------------------------------------------------------
        explicit            iterator( set_of_chars const & sc ) noexcept ;

        //!     Compiler-provided copy constructor.
        // -------------------------------------------------------------------
                            iterator( iterator const & ) = default ;

        //!     Compiler-provided copy-assignment operator.
        // -------------------------------------------------------------------
        iterator &          operator =( iterator const & ) = default ;

        //!\{   Iterator operations.
        // -------------------------------------------------------------------
        value_type          operator *() const noexcept ;
        iterator &          operator ++() & noexcept ;
        iterator            operator ++( int ) & noexcept ;

        //!     \note
        //!         It's undefined behavior to compare iterators into
        //!         different objects.
        // -------------------------------------------------------------------
        bool                operator ==( iterator const & ) const noexcept ;

        //!     \note
        //!         It's undefined behavior to compare iterators into
        //!         different objects.
        // -------------------------------------------------------------------
        bool                operator !=( iterator const & ) const noexcept ;
        //!\}

    private:
        bits_type const *   m_owner ;
        index_type          m_index ;

        void                increment() noexcept ;
        void                assert_refers_to_a_char() const noexcept ;
    } ;
} ;

template< typename FwdIterator>
set_of_chars::set_of_chars( FwdIterator begin, FwdIterator end ) noexcept
    :   m_bits()
{
    add( begin, end ) ;
}

template< typename FwdIterator >
set_of_chars &
set_of_chars::add( FwdIterator begin, FwdIterator end ) noexcept
{
    while ( begin != end ) {
        add( *begin ) ;
        ++ begin ;
    }
    return *this ;
}

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
