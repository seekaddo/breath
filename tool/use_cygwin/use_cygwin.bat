@echo off
REM =========================================================================
REM                       Copyright 2013 Gennaro Prota
REM
REM                 Licensed under the BSD 3-Clause License.
REM            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
REM              <https://opensource.org/licenses/BSD-3-Clause>)
REM _________________________________________________________________________
REM
REM     A quick tool to invoke before compiling with Cygwin, on
REM     Windows.

REM     The only important thing that this does is putting /usr/bin
REM     at the *end* of %PATH%, so that Cygwin's `link' isn't found
REM     before the homonym Microsoft linker.
REM
REM     Usage:
REM         1. invoke the Visual Studio Command Prompt of your choice
REM            (x86, x64, etc.)
REM         2. run this batch file.
REM

@echo on
setlocal

set CYGWIN_ROOT=C:\cygwin64
%CYGWIN_ROOT%\bin\mintty.exe -i /Cygwin-Terminal.ico --exec "./append_to_path.sh"

endlocal
