// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/encoding/binary_to_base64.hpp"
#include "breath/iteration/begin_end.hpp"
#include "breath/testing/testing.hpp"
#include <string>
#include <iterator>
#include <iostream>

void
check()
{
    //  A bunch of known base64 encodings. Some from RFC 3548 and some
    //  verified with:
    //      <https://www.base64encode.org/>.
    //  The latter is not an authoritative reference but I couldn't find
    //  any.
    //  ----------------------------------------------------------------
    struct
    {
        std::string binary ;
        std::string b64 ;
    } const             known[] =
    {
        { "A", "QQ==" },
        { "b", "Yg==" },
        { "AB", "QUI=" },
        { "ABC", "QUJD" },
        { "Hello", "SGVsbG8=" },
        { "Hello, world",  "SGVsbG8sIHdvcmxk" },
        { "Hello, world!", "SGVsbG8sIHdvcmxkIQ==" },
        { "\x14\xfb\x9c\x03\xd9\x7e", "FPucA9l+" }, // this example from RFC 3548
        { "\x14\xfb\x9c\x03\xd9",     "FPucA9k=" }, //   "     "      "  RFC 3548
        { "\x14\xfb\x9c\x03",         "FPucAw==" }, //   "     "      "  RFC 3548
        { "Long string long string long string long string",
          "TG9uZyBzdHJpbmcgbG9uZyBzdHJpbmcgbG9uZyBzdHJpbmcgbG9uZyBzdHJpbmc=" },
        { "The quick brown fox jumps over the lazy dog",
          "VGhlIHF1aWNrIGJyb3duIGZveCBqdW1wcyBvdmVyIHRoZSBsYXp5IGRvZw=="}
    } ;

    for ( auto it = breath::begin( known) ; it != breath::end( known) ; ++ it ) {
        std::string         out ;
        breath::binary_to_base64( it->binary.begin(), it->binary.end(),
                                    std::back_inserter( out ) ) ;
        BREATH_CHECK( out == it->b64 ) ;
    }
}

int
main()
{
    using namespace breath;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    test_descriptor const
                        desc[] =
    {
        check
    };

    test_runner::instance().run( begin( desc ), end( desc ) ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
