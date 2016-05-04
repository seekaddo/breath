// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/encoding/base64_to_binary.hpp"
#include "breath/iteration/begin_end.hpp"
#include "breath/testing/testing.hpp"
#include <string>
#include <iterator>
#include <iostream>

void
check_valid()
{
    //  The following array of vectors is almost identical to the one
    //  in
    //      binary_to_base64_test
    //  I have not put the code in common for two reasons:
    //  first the vectors here contain some newlines too, in order
    //  to check that the decoding function ignores them; and second
    //  because the two arrays might diverge in the future in order
    //  to accomodate particular tests for the base64->binary
    //  conversion.
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
        { "Hello, world",  "SGVs\nbG8s\nIHdv\ncmxk" },
        { "Hello, world!", "SGVsb\nG8sIH\ndvcmx\nkIQ==" },
        { "\x14\xfb\x9c\x03\xd9\x7e", "FPucA9l+" },// this example from RFC 3548
        { "\x14\xfb\x9c\x03\xd9",     "FPucA9k=" },//   "     "      "  RFC 3548
        { "\x14\xfb\x9c\x03",         "FPucAw==" },//   "     "      "  RFC 3548
        { "", "" },                                // this example from RFC 4648
        { "f", "Zg==" },                           //   "     "      "  RFC 4648
        { "fo", "Zm8=" },                          //   "     "      "  RFC 4648
        { "foo", "Zm9v" },                         //   "     "      "  RFC 4648
        { "foob", "Zm9vYg==" },                    //   "     "      "  RFC 4648
        { "fooba", "Zm9vYmE=" },                   //   "     "      "  RFC 4648
        { "foobar", "Zm9vYmFy" },                  //   "     "      "  RFC 4648
        { "Long string long string long string long string",
          "TG9uZyBzdHJpbmcgbG9uZyBzdHJpbmcgbG9uZyBzdHJpbmcgbG9uZyBzdHJpbmc=" },
        { "The quick brown fox jumps over the lazy dog",
          "VGhlIHF1aWNrIGJyb3duIGZveCBqdW1wcyBvdmVyIHRoZSBsYXp5IGRvZw=="}
    } ;

    for ( auto it = breath::cbegin( known) ; it != breath::cend( known) ; ++ it ) {
        std::string         out ;
        breath::base64_to_binary( it->b64.cbegin(), it->b64.cend(),
                                    std::back_inserter( out ) ) ;
        BREATH_CHECK( out == it->binary ) ;
    }
}

void
check_invalid()
{
    std::string const   invalid = "#AB"  ;
    std::string         out ;
    BREATH_CHECK_THROW( breath::base64_to_binary( invalid.cbegin(),
                                                  invalid.cend(),
                                                 std::back_inserter( out ) ) ) ;
}

int
main()
{
    using namespace breath;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    test_runner::instance().run( { check_valid, check_invalid } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
