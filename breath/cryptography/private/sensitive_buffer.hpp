// =========================================================================
//                   Copyright 2007-2008 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________
//
//!     \file
//!     \brief  A buffer for sensitive data.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_cYIOKCI73iMumaonvDavBYvSD0UPrlq4
#define BREATH_GUARD_cYIOKCI73iMumaonvDavBYvSD0UPrlq4

#include <cstddef>

namespace breath {

// This template is a quick hack to be replaced with a more
// complete solution
//
template< typename T >
class sensitive_buffer ;

template < typename T, std::size_t n >
class sensitive_buffer< T[ n ] >
{
    T m_data[ n ] ;

public:
    typedef std::size_t size_type ;
    typedef       T &   reference ;
    typedef T const &   const_reference ;
    typedef       T *   iterator ;
    typedef T const *   const_iterator ;

public:

    // construction
    sensitive_buffer() ;

    template< typename InputIter >
                        sensitive_buffer( InputIter begin, InputIter end ) ;

    explicit            sensitive_buffer( T const ( &src )[ n ] ) ;

    // destruction
                        ~sensitive_buffer() noexcept ;

    // iteration and access
    iterator            begin() ;
    iterator            end() ;

    const_iterator      begin() const ;
    const_iterator      end()   const ;

    reference           operator[]( size_type index ) ;
    const_reference     operator[]( size_type index ) const ;

private:
    void                wipe() ;
} ;


}

#include "sensitive_buffer.tpp"
#endif
// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
