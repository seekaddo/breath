//gps boilerplate
#include "breath/mathematics/next_multiple.hpp"
#include <climits>

////
#include "breath/diagnostics/assert.hpp"
#define DO_TEST(x) BREATH_ASSERT(x)
//////////

int
main()
{
    using               breath::next_multiple ;

    {
        DO_TEST( next_multiple( 8, 3 ) == 9 ) ;
        DO_TEST( next_multiple( 9, 3 ) == 12 ) ;
    }
}
