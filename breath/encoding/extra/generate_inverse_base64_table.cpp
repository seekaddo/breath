#include <vector>
#include <iostream>
#include <ostream>
#include <iterator>
#include <cstddef>
#include <iomanip>

int
main()
{
    static char constexpr
                        alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                     "abcdefghijklmnopqrstuvwxyz"
                                     "0123456789+/" ;

    int constexpr       size = 256 ;
    int constexpr       invalid = -1 ;
    std::vector< int >  table( size, invalid );
    for ( std::size_t i = 0 ; i < std::size( alphabet ) - 1 ; ++ i ) {
        table[ alphabet[ i ] ] = static_cast< int >( i ) ;
    }

    std::ostream &      os = std::cout ;

    os << "static int constexpr table[] = \n{\n    " ;
    for ( int i = 0 ; i < size ; ++ i ) {
        os << std::setw(2) << table[ i ] ;
        if ( i != ( size - 1 ) ) {
            os << ", " ;
        }
        if ( (i+1) % 16 == 0 ) {
            std::cout << "\n    " ;
        }
    }
    os << "\n} ;" << std::endl ;
}
