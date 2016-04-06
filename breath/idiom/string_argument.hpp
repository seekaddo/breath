// =========================================================================
//                       Copyright 2015 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#ifndef BREATH_GUARD_SCVOL7tEoh41fMb4HRZ21yR1tALwho7n#define BREATH_GUARD_SCVOL7tEoh41fMb4HRZ21yR1tALwho7n
#include <string>

namespace breath {

class string_argument
{
public:
                        string_argument( std::string const & ) ;
                        string_argument( char const * ) ;
    
    std::string         value() const ;

private:
    std::string         m_value ;
} ;

}
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
