// =========================================================================
//                       Copyright 2006 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

namespace breath {


template< class Device >
elapsed_timer< Device >::elapsed_timer( start_mode mode )
    : m_device()
{
    if( mode == auto_start) {
        restart();
    }
}

template< class Device >
void elapsed_timer< Device >::restart()
{
    return m_device.restart();
}

template< class Device >
typename elapsed_timer< Device >::duration_type
elapsed_timer< Device>::elapsed() const
{
    return m_device.elapsed();
}

template< class Device >
typename elapsed_timer< Device >::duration_type
elapsed_timer< Device >::resolution() const
{
    return m_device.resolution() ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
