# Author: Gennaro Prota
# gps add boilerplate!!

include ../../build/start.mk

# DESIGN GOALS:
#
#   - you specify the sources only (and the target, of course)
#
#     Le dipendenze dagli include sono calcolate con -MM. Ma iniziamo prima
#     con qualcosa di "manuale".


target = include_guard
libraries = advapi32.lib
            ##gps temp! (Windows only :-() --coupled with msvc.mk!!!

all: $(target)


$(target) : main$(object_file_suffix) macro_name$(object_file_suffix) entropy_source$(object_file_suffix) subrange_max$(object_file_suffix) last_api_error$(object_file_suffix) program_status$(object_file_suffix) exit_code$(object_file_suffix) exception$(object_file_suffix) assert$(object_file_suffix) string_argument$(object_file_suffix) base_filename$(object_file_suffix) allowed_path_separators$(object_file_suffix)
	$(link_to_exec)


macro_name$(object_file_suffix): macro_name.cpp \
 $(root)/tool/include_guard/macro_name.hpp \
 $(root)/breath/random/entropy_source.hpp \
 $(root)/breath/diagnostics/exception.hpp \
 $(root)/breath/random/subrange_adaptor.hpp \
 $(root)/breath/random/subrange_max.hpp


main$(object_file_suffix): main.cpp $(root)/breath/random/entropy_source.hpp \
 $(root)/breath/diagnostics/exception.hpp \
 $(root)/tool/include_guard/macro_name.hpp


entropy_source$(object_file_suffix) :      ../../breath/random/brt/entropy_source.cpp
	$(compile_to_object)


subrange_max$(object_file_suffix) : ../../breath/random/brt/subrange_max.cpp
	$(compile_to_object)

main$(object_file_suffix) : main.cpp
	$(compile_to_object)

macro_name$(object_file_suffix) : macro_name.cpp
	$(compile_to_object)

last_api_error$(object_file_suffix): ../../breath/diagnostics/brt/last_api_error.cpp
	$(compile_to_object)


program_status$(object_file_suffix): ../../breath/process/brt/program_status.cpp
	$(compile_to_object)

exit_code$(object_file_suffix): ../../breath/process/brt/exit_code.cpp
	$(compile_to_object)

exception$(object_file_suffix): ../../breath/diagnostics/brt/exception.cpp
	$(compile_to_object)

assert$(object_file_suffix): ../../breath/diagnostics/brt/assert.cpp
	$(compile_to_object)

string_argument$(object_file_suffix): ../../breath/idiom/brt/string_argument.cpp
	$(compile_to_object)

base_filename$(object_file_suffix): ../../breath/path/brt/base_filename.cpp
	$(compile_to_object)

allowed_path_separators$(object_file_suffix): ../../breath/path/brt/allowed_path_separators.cpp
	$(compile_to_object)
