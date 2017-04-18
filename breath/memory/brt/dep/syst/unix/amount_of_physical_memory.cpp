// =========================================================================
//                       Copyright 2017 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/memory/amount_of_physical_memory.hpp"

#include <unistd.h>

namespace breath {

unsigned long long
amount_of_physical_memory()
{
    unsigned long long const
                        pages = sysconf( _SC_PHYS_PAGES ) ;
    unsigned long long const
                        page_size = sysconf( _SC_PAGE_SIZE ) ;
    return pages * page_size / 1024 ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
