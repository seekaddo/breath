// =========================================================================
//                       Copyright 2015 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________


#include "breath/operator/comparison.hpp"

namespace breath {

template< typename IntegralType >
class counter
    :   private comparison< counter< IntegralType> >
{
public:
                        counter() ;
    //  PRE: n >= 0
    explicit            counter( IntegralType n ) ;
    counter &           operator ++() & ;
    counter             operator ++( int ) & ;
    counter &           operator --() & ;
    counter             operator --( int ) & ;

    IntegralType        value() const ;
    bool                is_equal( counter const & other ) const ;
    int                 compare(  counter const & other ) const ;

private:
    IntegralType        m_count ;
} ;

}

#include "brt/counter.tpp"

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
