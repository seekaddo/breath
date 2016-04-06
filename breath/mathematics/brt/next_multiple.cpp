//gps boilerplate

#include "breath/mathematics/next_multiple.hpp"
#include "breath/diagnostics/assert.hpp"

#include <climits>

namespace breath {

unsigned int
next_multiple( unsigned int a, unsigned int b )
{
    BREATH_ASSERT( a <= (UINT_MAX -b) ) ;
    return ( a/b + 1 ) * b ;
}

}