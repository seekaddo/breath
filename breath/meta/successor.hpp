// =========================================================================
//                       Copyright 2006 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#ifndef BREATH_GUARD_DjUmH0WQBIis1gQMNQWYhB7KQHMzHYQQ
#define BREATH_GUARD_DjUmH0WQBIis1gQMNQWYhB7KQHMzHYQQ

/*! \file   successor.hpp
    \brief
        Meta \c constant yielding the successor of its argument T

        \todo: document behavior in case of overflow
*/

#include "breath/meta/constant.hpp"

namespace breath {
namespace meta {

    template< typename T >
    class successor : public constant<
                                  typename T::value_type
                                  ,        T::value + 1
                              >
    {
    } ;

}
}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
