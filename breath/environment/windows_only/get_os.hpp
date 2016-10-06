// =========================================================================
//                       Copyright 2007 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________
//
//!     \file
//!     \brief Determines the running operating system.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_lc9dZp5eUrNd9dbNZHDcvW36RGyTlJ77
#define BREATH_GUARD_lc9dZp5eUrNd9dbNZHDcvW36RGyTlJ77

// gps add notices


#include "breath/environment/windows_only/os_id.hpp"

namespace breath {

    // note that this "determines" the running OS based on the information
    // returned by Windows itself: as such, it might be not the "true" OS. --gps
    os_id get_os();

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
