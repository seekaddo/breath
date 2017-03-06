# =========================================================================
#                       Copyright 2008 Gennaro Prota
#
#                 Licensed under the BSD 3-Clause License.
#            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
#             <https://opensource.org/licenses/BSD-3-Clause>.)
# _________________________________________________________________________
#
#       As usual, the options are listed "in groups", related to their purpose.
#       The group appearing first is related to standards conformance, including
#       (if necessary) removing macro definitions such as those for "min" and
#       "max" which are prohibited by the standard.
#
#       TODO: check this answer by Alf Steinbach:
#
#               <http://stackoverflow.com/questions/4913922/possible-problems-with-nominmax-on-visual-c>
#
#             What if we need to use GdiPlus?
#
#
#       Rationale
#       =========
#
#       /Za [not used]:
#
#           ideally I'd use this option everywhere, except for the
#           translation units including <Windows.h> (or other Windows
#           headers that need the Microsoft extensions).
#
#           BUT: can we assume that object files generated with /Za can
#           link with others that do not, without causing any undefined
#           behavior?  Even if /Za vs. /Ze was the only variation (i.e.
#           if *all* the other options were kept the same) I don't think
#           we can be sure. Thus I give up using /Za, for any source
#           file.
# ----------------------------------------------------------------------------

cpp_basic_options = /Zc:forScope        \
                    /Zc:wchar_t         \
                    /Zc:auto            \
                    /Zc:trigraphs       \
                    /Zc:rvalueCast      \
                    /Zc:strictStrings   \
                    /Zc:inline          \
                                        \
                    /EHs    \
                    /W4     \
                    /wd4996 \
                    /WX     \
                    /w14837   # enable a warning for trigraphs, even at level 1



include_switch = /I
object_file_suffix = .obj
exe_suffix = .exe

compiler_command = cl

linker_options = /WX /LTCG

# gps per tutte le compile_to_object, notare che usiamo $<.
#     Dobbiamo documentare che devono avere UN SOLO prerequisito?
define compile_to_object
$(compiler_command) $(cpp_options) /c /Fo$@ $<
endef

# gps Per tutte le link_to_exec, non dobbiamo passare anche $(cpp_options)?
#     Note that the /link option (and its arguments) must appear last.
#
#   We need to invoke the linker, not the compiler; but using cl.exe is handy
#   because it automatically translates some of the options that we have in the variable
#   $(cpp_options): e.g. /Zd -> /DEBUG. If we invoked link.exe directly, we'd need to
#   setup another variable, for the linker, with options in sync with the compiler ones. [gps]
define link_to_exec
$(compiler_command) $(cpp_options) /Fe$@  $+ /link $(linker_options) $(libraries)
endef

# Local Variables:
# mode: makefile
# indent-tabs-mode: t
# tab-width: 8
# End:
# vim: set ft=make noet ts=8 sts=0 sw=8:
