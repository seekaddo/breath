// Copyright 2013 Gennaro Prota [gps regen boilerplate!]
//
// Brent's algorithm for the determination of the period of a linear congruential
// function. -- gps la descrizione l'ho scritta all'impronta; sono poi da verificare terminologia e usi...

#include "breath/debugging/dump_expression.hpp"

// a{n+1} = ( alpha a{n} + beta ) mod m
template< typename T > // gps dichiaraz. da decidere
T
period( T ( &Fn )() )
{
    T y( Fn() ) ;
    int r = 1; // gps int?
    auto k = 0 ; // gps tipo di k da decidere (loop ma anche periodo!)
    
    T x ;
    int j ; // gps
    do {
        std::cout << "----------\n";
        x = y ;         BREATH_DUMP_EXPRESSION(x); BREATH_DUMP_EXPRESSION(y);
        j = k ;         BREATH_DUMP_EXPRESSION(j);// gps
        r *= 2 ;        BREATH_DUMP_EXPRESSION(r);

        std::cout << "inner loop\n";
        do {
            ++ k ;      BREATH_DUMP_EXPRESSION(k);
            y = Fn() ;  BREATH_DUMP_EXPRESSION(y);
        } while ( x != y && k < r ) ;

    } while ( x != y ) ;
    
    BREATH_DUMP_EXPRESSION(k-j);
    return k - j ;
    
}


#include <stdlib.h>
unsigned long long
linear_f()
{
#if 1
    static unsigned long long next = 1 ;

    int values[] = { 1, 7, 5, 3, 2 } ;
    ++ next;
    return values [next % ( sizeof values / sizeof values[0] )]; // (4*next + 1) % 7 ;//next = ( next * 1103515245 + 12345 ) % ( 1ull << 32 ) /*% (1ull << 16)*/;
    
#else

    return rand() ;
#endif
}

#include <iostream>
#include <ostream>


int main()
{
    srand( 0 ) ;

    for ( int i = 0 ; i < 37; ++ i )
        std::cout << i << " " << linear_f() << std::endl ;

    auto p = period( linear_f ) ;
    std::cout << "Determined period: " << p << " (" << (log(p*1.0)/log(2.0)) << " bit)" << std::endl ;
}
