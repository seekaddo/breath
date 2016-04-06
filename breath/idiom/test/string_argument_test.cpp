//gps boilerplate

#include "breath/idiom/string_argument.hpp"

/////////
#include "breath/diagnostics/assert.hpp"
#define DO_TEST( x ) BREATH_ASSERT( x )
//////

int
main()
{
    // construction
    {
        std::string const   s( "test" );
        breath::string_argument
                            arg( s ) ;
        DO_TEST( arg.value() == "test" ) ;

        char const *        s2 = "test-2" ;
        breath::string_argument
                            arg2( s2 ) ;
        DO_TEST(arg2.value() == "test-2" ) ;
    }

}