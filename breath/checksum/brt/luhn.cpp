// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/checksum/luhn.hpp"
#include "breath/counting/count.hpp"
#include "breath/diagnostics/exception.hpp"
#include <cctype>
#include <cstddef>
#include <numeric>

namespace breath {
namespace        {

constexpr int       table[] = { 0, 2, 4, 6, 8, 1, 3, 5, 7, 9 } ;
constexpr int       base = static_cast< int >( breath::count( table ) ) ;

}

int
luhn_sum( std::string const & s )
{
    bool                from_table = false ;
    auto lambda = [ & ]( int s, char c )
    {
        if ( ! std::isdigit( c ) ) {
            throw exception( "non-digit char in Luhn string" ) ;
        }
        int const           value = c - '0' ;
        int const           sum = s + ( from_table
                                          ? table[ value ]
                                          : value ) ;
        from_table = ! from_table ;
        return sum % base ;
    } ;

    return std::accumulate( s.crbegin(), s.crend(), 0, lambda ) ;
}

bool
has_luhn_sum( std::string const & s )
{
    return luhn_sum( s ) == 0 ;
}

char
luhn_check_digit( std::string const & s )
{
    int const           sum = luhn_sum( s + '0' ) ;
    return '0' + ( ( base - sum ) % base ) ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
