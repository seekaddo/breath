// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/cpu/cpuid.hpp"

#include <string>
#include <ostream>
#include <iostream>
#include <cstring>


bool
has_processor_brand_string()
{
    if ( ! is_cpuid_supported() ) {
        return false ;
    }

    unsigned const      mask = 0x8000'0000 ;
    cpuid_result const  r = get_cpuid_info( mask, 0 ) ;

    return (r.eax & mask) != 0 &&
        r.eax >= (mask + 4) ;
}


std::string
processor_brand_string()
{
    // Reference: Intel Manual, 3-176, Vol. 2A
    //
    unsigned const      from = 0x80000002 ;
    unsigned const      to   = 0x80000004 ;

    std::size_t const   len = 16 * ( to - from + 1 ) ;
    char                s[ len ] ;
    for ( unsigned i = from ; i <= to ; ++ i ) {
        cpuid_result const info = get_cpuid_info( i, 0 ) ;
        char * const        p = s + 16 * ( i - from ) ;
        std::memcpy( p,      &info.eax, sizeof( info.eax ) ) ;
        std::memcpy( p + 4,  &info.ebx, sizeof( info.ebx ) ) ;
        std::memcpy( p + 8,  &info.ecx, sizeof( info.ecx ) ) ;
        std::memcpy( p + 12, &info.edx, sizeof( info.edx ) ) ;
    }
    return std::string( s ) ;
}


std::string
cpu_vendor_id_string()
{
    cpuid_result const r = get_cpuid_info( 0, 0 ) ;

    int const           len = 12 ;
    char                id_string[ len ] ;
    *reinterpret_cast< int * >( id_string + 0 ) = r.ebx ;
    *reinterpret_cast< int * >( id_string + 4 ) = r.edx ;
    *reinterpret_cast< int * >( id_string + 8 ) = r.ecx ;
    return std::string( id_string, len ) ;
}


int
main()
{
    std::cout << "CPU vendor ID string: " << cpu_vendor_id_string() << std::endl ;
    std::cout << "Processor brand string: " << ( has_processor_brand_string()
                                                    ? processor_brand_string()
                                                    : "<not available>" )
                                            << std::endl;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
