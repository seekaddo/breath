#! /bin/sh --
# =========================================================================
#                    Copyright 2007-2008 Gennaro Prota
#
#                 Licensed under the BSD 3-Clause License.
#            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
#              <https://opensource.org/licenses/BSD-3-Clause>)
# _________________________________________________________________________
#
#       init_file.sh:
#       =============
#
#       This script must be used to initialize all text files intended
#       for Breath C++. It ensures, among other things, that our
#       copyright notice and license reference (plus, guards for C++
#       includes) are inserted. See the documentation for further
#       details.
# ----------------------------------------------------------------------------

.   "$BREATH_ROOT/tool/shell/script.shc"
.   "$BREATH_ROOT/tool/shell/file_name.shc"
.   "$BREATH_ROOT/tool/shell/string.shc"
.   "$BREATH_ROOT/tool/shell/new_line.shc"
.   "$BREATH_ROOT/tool/shell/copyright.shc"

make_opening_line()
{
    case "$language" in
    AWK)
        printf '%s\n' '#! /bin/awk -f'
        ;;
    Batch)
        printf '%s\n' '@echo off'
        ;;
    CSS)
        printf '%s\n' '@charset "UTF-8";'
        ;;
    Emacs-Lisp)
        printf '%s\n\n' ";;; $base_name --- TODO: description"
        ;;
    Shell)
        if [ "$name_extension" != 'shc' ]
        then
            printf '%s\n' '#! /bin/sh --'
        fi
        ;;
    XSLT)
        printf '%s\n' '<?xml version="1.0" encoding="UTF-8"?>'
        ;;
    esac
}

mark_section()
{
    if [ -z "$prefix" ]
    then
        case "$1" in
        start)
            printf '%s\n' "$block_comment_start"
            ;;
        end)
            printf '%s\n' "$block_comment_end"
            ;;
        esac
    fi
}

get_line_width()
{
    printf '%s' '78'
}

dump()
{
    # the variables are passed in the environment to awk only
    #
    #
    prefix="$prefix"                        \
    min_prefix_pad=5                        \
    width=` get_line_width `                \
    comment_pattern="$comment_pattern"      \
    alignment="$2"      awk -f "$BREATH_ROOT/tool/prefixed_dump.awk" "$1"
}



#       Main
# ============================================================================
if [ -z "$BREATH_ROOT" ] || [ -z "$BREATH_CONTRIBUTOR" ]
then
    quit_script 'Define both $BREATH_ROOT and $BREATH_CONTRIBUTOR'
fi

full_path="$1"
base_name=` get_base_name "$full_path" `
name_extension=` get_extension "$full_path" `

if [ -z "$full_path" ]
then
    quit_script 'no file name provided'
elif [ -z "$name_extension" ]
then
    quit_script 'Breath file names must have an extension'
fi


#       Find the language corresponding to the name extension and
#       extract the relevant data about it
# ----------------------------------------------------------------------------
language=""
traits_file="$BREATH_ROOT/tool/init_file/language_traits.txt"
comment_pattern='^[:space:]*#'

eval ` awk '
    /'"$comment_pattern"'/ {
        next
    }
    NF > 4 && "'"$name_extension"'" ~ "^"$1"$"  {
        printf( "block_comment_start='\''%s'\''\n", $2 )
        printf(   "block_comment_end='\''%s'\''\n", $3 )
        printf(  "line_comment_start='\''%s'\''\n", $4 )
        printf(            "language='\''%s'\''\n", $5 )

        exit

    }' "$traits_file" `

if [ -z "$language" ]
then
    quit_script "filename extension not found in $traits_file"
fi

absent='no'
prefix=""
if [ "$line_comment_start" != "$absent" ]
then
    prefix="$line_comment_start"
fi

tool_root="$BREATH_ROOT/tool"
exe_root="$BREATH_ROOT/exec"

#       Header
# ----------------------------------------------------------------------------
make_opening_line
mark_section start

(
    width=` get_line_width `
    row1=` make_string "$width" '=' `
    row2=` make_string "$width" '_' `
    printf '%s\n' "$row1"
    make_copyright_notice "$BREATH_CONTRIBUTOR"
    new_line '1'
    cat "$tool_root/init_file/license_reference.txt"
    printf '%s\n' "$row2"
)                                                       | dump - 'align_center'

mark_section end

#       Body
# ----------------------------------------------------------------------------
blank_lines='8'                      # gps do we single-quote number-literals?
if [ "$language" = 'C++' ]
then
    if [ "$name_extension" = 'hpp' ]
    then
        if [ -x "$exe_root/include_guard" ] ##gps check with POSIX!!
        then
            (printf '\nnamespace breath {'; new_line "$blank_lines"; printf '}\n') |
                "$exe_root/include_guard"
        else
            printf '%s\n' "Cannot find the include_guard tool. Did you build it?"
        fi
    else
        printf '\nnamespace breath {\n\n}\n\n'
    fi
else
    new_line "$blank_lines"
fi
#       Trailer
# ----------------------------------------------------------------------------
mark_section start
"$tool_root/init_file/make_file_trailer.sh" "$language" | dump - 'align_left'

mark_section end

if [ "$language" = 'Emacs-Lisp' ]
then
    # Not essential but... when in Rome... :-)
    printf '\n%s\n' ";;; $base_name ends here"
fi

# Local Variables:
# mode: shell-script
# indent-tabs-mode: nil
# sh-indentation: 4
# End:
# vim: set ft=sh et sts=4 sw=4:
