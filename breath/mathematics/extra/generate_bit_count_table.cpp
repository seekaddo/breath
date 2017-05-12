// =========================================================================
//                       Copyright 2017 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include <array>
#include <cstddef>
#include <iostream>
#include <string>

int
main()
{
    constexpr int       size = 256 ;
    std::array< std::uint_fast32_t, size >
                        table ;

    class               bit_count
    {
    public:
        std::size_t     operator()() noexcept
        {
            unsigned    value = m_n ;
            std::size_t         count = 0 ;
            while ( value != 0 ) {
                ++ count ;
                value &= ( value - 1 ) ;
            }
            ++ m_n ;
            return count ;
        }
    private:
        unsigned int    m_n = 0 ;
    } ;

    std::generate( table.begin(), table.end(), bit_count{} ) ;
    constexpr int       numbers_per_line = 16 ;
    constexpr int       indent_size = 4 ;
    std::string const   indent( indent_size, ' ' ) ;

    std::ostream &      os = std::cout ;

    os << "constexpr unsigned char"              << std::endl
       << "                    count_table[] = " << std::endl
       << "{"                                    << std::endl ;
    os << indent ;
    for ( int i = 0 ; i < size ; ++ i ) {
        os << table[ i ] ;
        if ( i != ( size - 1 ) ) {
            os << ',' ;
        }
        if ( ( i + 1 ) % numbers_per_line == 0 &&
             i != ( size - 1 ) ) {
            os << '\n' << indent ;
        } else if ( i != ( size - 1 ) ) {
            os << ' ' ;
        } else {
            os << std::endl ;
        }
    }
    os << "} ;" << std::endl ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4: