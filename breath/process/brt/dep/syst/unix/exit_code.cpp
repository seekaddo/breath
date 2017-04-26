// =========================================================================
//                    Copyright 2006-2010 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

namespace breath {

// NB (if you add/remove/change values):
//
// * on POSIX conforming systems "only the least significant 8
// bits (that is, status & 0377) shall be available to a waiting parent
// process", so stay below 256
//
// * many de facto conventions exist and it is generally better to stay below 64
// anyway

int const           exit_warning(  10 ) ;
int const           exit_error(    20 ) ;
int const           exit_fatal(    30 ) ;
int const           exit_internal( 59 ) ;

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:

