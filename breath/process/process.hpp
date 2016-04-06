// =========================================================================
//                       Copyright 2015 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#ifndef BREATH_GUARD_ZrGNfF85u9RhKIbhXAPdD2JlFPjWlGjV
#define BREATH_GUARD_ZrGNfF85u9RhKIbhXAPdD2JlFPjWlGjV

#include "breath/process/private/process_id_type.hpp"
#include "breath/idiom/declare_non_copyable.hpp"
#include "breath/idiom/maybe.hpp"
#include <cstddef>
#include <string>

namespace breath {

class process
{
    BREATH_DECLARE_NON_COPYABLE( process ) ;
public:
    typedef process_id_type
                        id_type ;

                        process() ;
                        ~process() ;
    id_type             id() const ;

    void                start( std::string const & app_name,
                               std::string const & arguments,
                               maybe<std::size_t> timeout_in_ms =
                                                    maybe<std::size_t>() ) ;
    void                kill() ;
    void                terminate() ;

private:
    class               impl ;
    impl * const        m_impl ;
} ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
