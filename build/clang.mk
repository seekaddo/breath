# =========================================================================
#                       Copyright 2013 Gennaro Prota
#
#                 Licensed under the BSD 3-Clause License.
#            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
#              <https://opensource.org/licenses/BSD-3-Clause>)
# _________________________________________________________________________

# NOTE: for the moment (or not?), include gcc.mk then
#       override what needs to be overridden.  --gps
#
include $(root)/build/gcc.mk

cpp_basic_options = -std=c++14       \
                    -Wall            \
                    -Wextra          \
                    -Werror          \
                    -pedantic-errors \
            -D_POSIX_C_SOURCE=200112L

cpp_extra_options = -pipe	\
# gps queste vanno nel debug:
#cpp_extra_options += -fcatch-undefined-behavior

#                    -fdiagnostics-show-name \
#                    -verify     #OK?? gps


cpp_extra_options += -isystem"/usr/lib/gcc/i686-pc-cygwin/4.7.3/include/c++"  ### ^^^^^gps TEMP!!!!
cpp_extra_options += -isystem"/usr/lib/gcc/i686-pc-cygwin/4.7.3/include/c++/i686-pc-cygwin" ## gps temp


compiler_command = clang++

# Local Variables:
# mode: makefile
# indent-tabs-mode: t
# tab-width: 8
# End:
# vim: set ft=make noet ts=8 sts=0 sw=8:
