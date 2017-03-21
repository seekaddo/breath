// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include <array>
#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <ios>
#include <iostream>
#include <ostream>
#include <string>

int
main()
{
    constexpr int       size = 256 ;
    std::array< std::uint_fast32_t, size >
                        table;
    typedef std::uint_fast32_t
                        fast32_type ;

    class               byte_checksum
    {
    public:
        fast32_type operator()() noexcept
        {
            constexpr fast32_type
                                reversed_polynomial( 0xEDB88320uL ) ;
            constexpr int       char_bit( 8 ) ;
            auto checksum = static_cast< fast32_type >( m_n ) ;
            ++ m_n ;

            for ( int i = 0 ; i < char_bit ; ++ i ) {
                checksum = ( checksum >> 1 ) ^ ( checksum % 2 == 0
                                                    ? 0
                                                    : reversed_polynomial ) ;
            }
            return checksum ;
        }
    private:
        unsigned long long
                        m_n = 0 ;
    } ;
    std::generate( table.begin(), table.end(), byte_checksum{} ) ;
    int constexpr       numbers_per_line = 6 ;
    int constexpr       indent_size = 4 ;
    std::string const   indent( indent_size, ' ' ) ;

    std::ostream &      os = std::cout ;

    os.setf( std::ios_base::hex, std::ios_base::basefield ) ;
    os.fill( '0' ) ;
    os << "static constexpr std::uint_fast32_t table[] =\n{\n" << indent ;
    for ( int i = 0 ; i < size ; ++ i ) {
        os << "0x" << std::setw( 8 ) << table[ i ] ;
        if ( i != ( size - 1 ) ) {
            os << ',' ;
        }
        if ( (i+1) % numbers_per_line == 0 ) {
            std::cout << '\n' << indent ;
        } else if ( i != ( size - 1 ) ) {
            std::cout << ' ' ;
        }
    }
    os << "\n} ;" << std::endl ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
