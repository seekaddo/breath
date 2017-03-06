// =========================================================================
//                       Copyright 2015 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________
//
//!     \file
//!     \brief Represents a Win32 process.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_R609ymqmTeLeF2v3mTEcOyW8AqCEibGg
#define BREATH_GUARD_R609ymqmTeLeF2v3mTEcOyW8AqCEibGg

#include "breath/process/process.hpp"
#include <cstddef>
#include <string>

namespace breath {

class win32_process
    :   public process
{
public:
     //                   win32_process( process_id_type id ) ;
    std::string         name() const ;
    std::size_t         module_count() const ;
};

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
