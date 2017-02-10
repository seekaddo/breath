// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________
//
//!     \file
//!     \brief Universally unique identifiers.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_jjJFg8dCizQ6ClSYgT8Zsg2zo7zFYgfG
#define BREATH_GUARD_jjJFg8dCizQ6ClSYgT8Zsg2zo7zFYgfG

#include <cstdint>
#include <cstddef>
#include <iosfwd>

namespace breath {

class uuid
{
public:
    enum variant { reserved, rfc_4122, microsoft, future } ;
    enum version { time_based, dce_security, name_based_md5, pseudo_random,
                   name_based_sha1 } ;

    typedef uint8_t     value_type ;
    typedef value_type const &
                        const_reference ;
    typedef value_type const *
                        const_iterator ;
    typedef std::size_t size_type ;
    typedef std::ptrdiff_t
                        difference_type ;

                        uuid( variant, version ) ;

private:
    uint32_t            m_time_low ;
    uint16_t            m_time_mid ;
    uint16_t            m_time_hi_and_version ;
    uint16_t            m_clock_seq ;
    uint8_t             m_node[ 6 ] ;

    friend std::ostream & operator <<( std::ostream &, uuid const & ) ;
} ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
