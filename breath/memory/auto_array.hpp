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

template< typename T >
class auto_array
{
    BREATH_DECLARE_NON_COPYABLE( auto_array )

public:
                        auto_array() noexcept ;
    explicit            auto_array( T * ) noexcept ;
                        ~auto_array() noexcept ;

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
