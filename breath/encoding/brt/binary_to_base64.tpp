// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include <climits>
#include <cstddef>
#include <type_traits>

namespace breath {

template< typename InputIter, typename OutputIter >
void
binary_to_base64( InputIter begin, InputIter end, OutputIter out )
{
    static_assert( CHAR_BIT == 8
               && (std::is_same< typename InputIter::value_type, char >::value
      || std::is_same< typename InputIter::value_type, unsigned char>::value),
     "" ) ;

    static char const   alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                     "abcdefghijklmnopqrstuvwxyz"
                                     "0123456789+/" ;
    int const           group_size( 3 ) ;
    auto                curr( begin ) ;
    int                 count( 0 ) ;

    //  This code is ugly because we stick to input iterators and don't
    //  assume random access. Furthermore we have to check for the end
    //  of the range at each increment.
    //  ------------------------------------------------------------------
    while ( curr != end ) {
        *out = alphabet[ static_cast< unsigned char>( *curr ) >> 2 ] ;
        ++ count ;
        ++ out ;
        auto                tmp = ( static_cast< unsigned char >( *curr )
                                                             & 0x03 ) << 4 ;
        
        if ( ++curr != end ) {
            ++ count ;
            tmp |= ( static_cast< unsigned char >( *curr ) & 0xf0 ) >> 4 ;
            *out = alphabet[ tmp ] ;
            ++ out ;

            auto            tmp2 = ( static_cast< unsigned char >( *curr )
                                                                & 0x0f ) << 2 ;
            if ( ++curr != end ) {
                ++ count ;
                tmp2 |= static_cast< unsigned char >( *curr ) >> 6 ;
                *out = alphabet[ tmp2 ] ; 
                ++ out ;
                *out = alphabet[ static_cast< unsigned char >( *curr ) & 0x3f ] ;
                ++ out ;
                ++ curr ;
            } else {
                *out = alphabet[ tmp2 ] ;
                ++ out ;
            }
        } else {
            *out = alphabet[ tmp ] ;
            ++ out ;
        }
        count %= group_size ;
    }

    for ( int i = 0 ; i < ( group_size - count ) % group_size ; ++ i ) {
        *out++ = '=';
    }
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
