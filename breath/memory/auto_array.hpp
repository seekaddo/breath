// =========================================================================
//                       Copyright 2006 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#ifndef BREATH_GUARD_FvaoTt7c3pTltKsed1Av5CAvE3SvnVIn
#define BREATH_GUARD_FvaoTt7c3pTltKsed1Av5CAvE3SvnVIn

#include "breath/idiom/declare_non_copyable.hpp"

namespace breath {

//      auto_array< T >
//      ===============
//!
//!     A smart pointer that retains sole ownership of an array through
//!     a pointer. This template is similar to
//!
//!       template < typename T,
//!                  typename Deleter
//!                > class unique_ptr< T[], Deleter > ;
//!     but was written way before C++11.
//!
//!     Like for unique_ptr, instances of this template satisfy the
//!     requirements of MoveConstructible and MoveAssignable, but not
//!     the requirements of either CopyConstructible or CopyAssignable.
// ---------------------------------------------------------------------
template< typename T >
class auto_array
{
public:
    BREATH_DECLARE_NON_COPYABLE( auto_array )

                        auto_array() noexcept ;
    explicit            auto_array( T * ) noexcept ;
                        auto_array( auto_array && ) noexcept ;
                        ~auto_array() noexcept ;

    auto_array< T > &   operator=( auto_array && ) noexcept ;
    T *                 get() noexcept ;
    T const *           get() const noexcept ;
    void                reset( T * ) noexcept ;

private:
    T *                 m_ptr ;
    void                do_delete() noexcept;
} ;

}

#include "brt/auto_array.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
