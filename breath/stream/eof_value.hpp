// ===========================================================================
//                        Copyright 2011 Gennaro Prota
//
//                 Licensed under the Simplified BSD License.//gps
//            (See accompanying file SIMPLIFIED_BSD_LICENSE.txt or
//              <http://opensource.org/licenses/bsd-license.php>)
// ___________________________________________________________________________
//
//
//      A convenience source file to separate out the crazy #includes
//      required for using EOF or char_traits<...>::eof():
//
//        1. the former would require including <stdio.h> or <cstdio>
//        2. the latter would require <string>
//
//      Both choices are IMHO particularly annoying for maintenance
//      and code review: any reader of the code would probably wonder,
//      for (1), why you include <cstdio> if you are using C++ streams
//      (and not stdio); and, for (2), why you include <string> even
//      where there's no usage of std::string.
//
//      The root of the issue is the poor header partitioning of the
//      standard library but we can't do anything about that. We can,
//      however, separate things out so that the relevant #includes
//      are insulated. Which is the only real purpose of this
//      facility.
//
//      NOTE: there's no .tpp file, here; it seemed just overkill.
//            Also, it seems natural to add an is_eof_value(), too,
//            since using eq_int_type would still require #including
//            the <string> header.
//
// ---------------------------------------------------------------------------

#ifndef BREATH_EOF_VALUE_HPP_2011313OldFV9EUJ3nWdeEF4AQeSB3e
#define BREATH_EOF_VALUE_HPP_2011313OldFV9EUJ3nWdeEF4AQeSB3e

#include <string>

namespace breath {

template< typename Stream >
typename Stream::int_type
eof_value( Stream const & )
{
    return Stream::traits_type::eof() ;
}

template< typename IntType, typename StreamBuf >
bool
is_eof_value( IntType x )
{
    return StreamBuff::traits_type::eq_int_type( pfm(),
            StreamBuf::traits_type::eof() ) ;
}






}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
