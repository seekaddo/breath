// =========================================================================
//                       Copyright 2008 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#ifndef BREATH_GUARD_fuCxVYYJ2LdcmZesVYlZ9PyrSKmKj97I
#define BREATH_GUARD_fuCxVYYJ2LdcmZesVYlZ9PyrSKmKj97I

// Adapts a random or pseudorandom number generator to emit numbers in
// a subrange of its original range (see the subrange_max facility).
//
// NB: does NOT support min < 0 !!!

#include "breath/random/subrange_max.hpp"
#include "breath/diagnostics/assert.hpp"

namespace breath {

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
                        subrange_adaptor( Engine & e, result_type new_max ) : m_engine( e ), m_max( new_max ) {
                                BREATH_ASSERT( m_max <= m_engine.max() ) ;
                            } ///gps move to .cpp


    result_type         next()
    {
        if ( m_engine.max() == m_max ) {
            return m_engine.next() ; // subrange coincides with full range
        }

        auto                n ( m_engine.next() ) ;
        unsigned long const sub_max =
                        breath::subrange_max( m_max, m_engine.max() ) ;
        while ( n > sub_max ) {
            n = m_engine.next() ;
        }
        return n % ( m_max + 1 ) ;
    }

} ;



}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
