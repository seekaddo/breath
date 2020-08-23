@echo off
REM ==========================================================================
REM                        Copyright 2013 Gennaro Prota
REM
REM                  Licensed under the 3-Clause BSD License.
REM             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
REM              <https://opensource.org/licenses/BSD-3-Clause>.)
REM __________________________________________________________________________
REM
REM     A quick tool to invoke before compiling with Cygwin, on Windows.
REM
REM     The only important thing that this does is putting /usr/bin at
REM     the *end* of %PATH%, so that Cygwin's `link' isn't found before
REM     the homonym Microsoft linker.
REM
REM     Usage: see the top-level read_me.
REM --------------------------------------------------------------------------

setlocal

set CYGWIN_ROOT=C:\cygwin64
%CYGWIN_ROOT%\bin\mintty.exe --icon /Cygwin-Terminal.ico    ^
                             --exec "./append_to_path.sh"

endlocal

REM Local Variables:
REM mode: bat
REM indent-tabs-mode: nil
REM batch-indent-level: 4
REM End:
REM vim: set ft=dosbatch et sts=4 sw=4:
