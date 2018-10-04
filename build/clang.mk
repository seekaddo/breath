# =========================================================================
#                    Copyright 2013-2018 Gennaro Prota
#
#                 Licensed under the 3-Clause BSD License.
#            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
#             <https://opensource.org/licenses/BSD-3-Clause>.)
# _________________________________________________________________________

#       As usual, the options are listed in two groups. The group
#       listed first relates mainly to standards conformance. The other
#       group contains other options in alphabetical order.
#
#       Special notes for some of the options:
#       ======================================
#
#       (See gcc.mk)
# ----------------------------------------------------------------------------
cpp_basic_options =  -std=c++14                 \
                     -Weverything               \
                     -Wno-c++98-compat          \
                     -pedantic                  \
                     -Werror                    \
                     -D_POSIX_C_SOURCE=200112L  \
                     -U_GNU_SOURCE              \
                     -D_GLIBCXX_USE_CXX11_ABI

cpp_basic_options += -pipe

# gps queste vanno nel debug:
#cpp_extra_options += -fcatch-undefined-behavior

#                    -fdiagnostics-show-name \
#                    -verify     #OK?? gps


include_switch = -I
object_file_suffix = .o

# Note that this differs from the compiler name, which is in $(compiler)
#
compiler_command = clang++

# gps mostly by James!
define compile_to_object
# gps controlla la riga seguente!!!
$(compiler_command) $(cpp_options) -c -o $@ $<
endef

# gps mostly by James!
#
define link_to_exec
$(compiler_command) $(cpp_options) -o $@ $+
endef


# Local Variables:
# mode: makefile
# indent-tabs-mode: t
# tab-width: 8
# End:
# vim: set ft=make noet ts=8 sts=0 sw=8:
