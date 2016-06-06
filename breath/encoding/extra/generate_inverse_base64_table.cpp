#include <vector>
#include <iostream>
#include <ostream>
#include <iterator>
#include <cstddef>
#include <iomanip>

int
main()
{
    static constexpr char
                        alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                     "abcdefghijklmnopqrstuvwxyz"
                                     "0123456789+/" ;

    constexpr int       size = 256 ;
    constexpr int       invalid = -1 ;
    std::vector< int >  table( size, invalid );
    for ( std::size_t i = 0 ; i < std::size( alphabet ) - 1 ; ++ i ) {
        table[ alphabet[ i ] ] = static_cast< int >( i ) ;
    }

    std::ostream &      os = std::cout ;

    os << "static constexpr int table[] = \n{\n    " ;
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
