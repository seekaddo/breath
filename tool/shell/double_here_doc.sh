#! /bin/sh --
#  ===========================================================================
#                         Copyright 2009 Gennaro Prota
#
#                 Licensed under the BSD 3-Clause License.
#            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
#             <https://opensource.org/licenses/BSD-3-Clause>.)
#  ___________________________________________________________________________

.   "$BREATH_ROOT/tool/shell/here_document.shc"

: <<eof1; : <<eof2
Hello,
eof1
World!
eof2


dump_here_document 'eof1'

# Local Variables:
# mode: shell-script
# indent-tabs-mode: nil
# sh-indentation: 4
# End:
# vim: set ft=sh et sts=4 sw=4:
