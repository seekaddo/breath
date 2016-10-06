// =========================================================================
//                       Copyright 2006 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/path/base_filename.hpp"
#include "breath/path/allowed_path_separators.hpp"
#include <string>

namespace breath {

std::string
base_filename( string_argument const & full_path )
{
    std::string const   s( full_path.value() ) ;
    std::string::size_type const
                        pos = s.find_last_of(
                                breath::allowed_path_separators() ) ;
    return pos == std::string::npos
                    ? s
                    : s.substr( pos + 1 )
                    ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
