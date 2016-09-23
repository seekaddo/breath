// =========================================================================
//                       Copyright 2008 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________
//
//!     \file
//!     \brief Random or pseudo-random number generator adaptor.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_fuCxVYYJ2LdcmZesVYlZ9PyrSKmKj97I
#define BREATH_GUARD_fuCxVYYJ2LdcmZesVYlZ9PyrSKmKj97I

namespace breath {

//!     Adapts a random or pseudorandom number generator to emit
//!     numbers in a subrange of its original range (see the
//!     subrange_max facility).
//
//!     NB: does NOT support min < 0 !!!
//
template< typename Engine >
class subrange_adaptor
{
public:
    typedef typename Engine::result_type
                        result_type ;
private:
    Engine &            m_engine ; ///gps A reference, until I'll work out copyability issues
    result_type const   m_max    ;

    void operator=(subrange_adaptor const & ) ; //gps get away with VC++'s C4512, for now

public:
                        subrange_adaptor( Engine & e, result_type new_max ) ;
    result_type         next() ;
} ;



}

#include "brt/subrange_adaptor.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
