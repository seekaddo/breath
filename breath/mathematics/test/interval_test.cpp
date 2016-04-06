#include "breath/mathematics/interval.hpp"

// --------------------
// gps use of assert is temporary
#if defined NDEBUG
#   error
#endif
#include <assert.h>
#define DO_TEST( x ) assert( x )
// --------------------


// gps OK questo test è quasi inutile; come faccio a templatizzare?
template< typename T >
void
do_test()
{
    using breath::interval ; //gps rimuovere dopo?

    // test empty interval(s) //gps "plural"?
    {
        interval< T >       empty( 5, 4 ) ;
        DO_TEST( ! empty.contains( 4 ) ) ;
        DO_TEST( ! empty.contains( 5 ) ) ;
        DO_TEST( ! empty.contains( 0 ) ) ;
        DO_TEST( ! empty.contains( 1 ) ) ;

    }

    interval< T >       itv( 1, 10 ) ;
    DO_TEST( itv.contains( 5 ) ) ;
    DO_TEST( ! itv.contains( 0 ) ) ;
    
}

int
main()
{
    do_test< int >() ;
}