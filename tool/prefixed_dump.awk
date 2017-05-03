#! /bin/awk -f
# =========================================================================
#                       Copyright 2008 Gennaro Prota
#
#                 Licensed under the 3-Clause BSD License.
#            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
#             <https://opensource.org/licenses/BSD-3-Clause>.)
# _________________________________________________________________________
#
#       Arguments:
#       ----------
#
#       All arguments must be passed via awk's ENVIRON (for the
#       rationale, see our Scripting Guidelines). They are:
#
#       * alignment
#           One of 'align_right', 'align_center', 'align_left'  [gps]
#       * prefix
#           A string to be prefixed to every line of the input; can be
#           empty
#       * min_prefix_pad
#           A non-negative integer specifying the minimum character
#           length of each line prefix: if the prefix is shorter
#           than min_prefix_pad, spaces are added at the right;
#           otherwise the prefix and exactly one space after it are
#           output (e.g. min_prefix_pad=3 -> "//  " or "rem ")
#       * width
#           An integer >= min_prefix_pad, (gps) integer giving the
#           maximum length in characters of the whole output line
#           (including prefix)
#       * comment_pattern
#           An ERE. Input lines matching this regular expression are
#           considered "comments": they yield no corresponding output
# ----------------------------------------------------------------------------

function max( a, b )
{
    return a < b ? b : a
}

function centered( text, room )
{
    len =               length( text )
    pad = len > room ?  0                               \
                     :  int( ( room - len ) / 2 )

    return sprintf( "%*s", pad + len, text )
}

BEGIN {
    alignment =       ENVIRON[ "alignment" ]
    prefix =          ENVIRON[ "prefix" ]
    min_prefix_pad =  ENVIRON[ "min_prefix_pad" ]
    width =           ENVIRON[ "width" ]
    comment_pattern = ENVIRON[ "comment_pattern" ]

    prefix_pad = max( min_prefix_pad, length( prefix ) + 1 )
}

$0 ~ comment_pattern {
    next
}

length() == 0 {
    print prefix
    next
}

{
    #printf( "%-*s", prefix_pad, prefix )
    printf( "%s ", prefix ) ## gps cambiato per Breath, in modo da non avere
                     ## più spazi dopo il comment marker (nota che nel
                     ## calcolo del centramento prefix_pad viene considerato
                     ## comunque)

    room = width - prefix_pad
    text = substr( $0, 1, room ) # this may truncate

    if ( alignment == "align_center" ) {
        print centered( text, room )
    } else if ( alignment == "align_right" ) {
        # not implemented - gps
    } else {
        # align to left and be done with it
        print text
    }
}
