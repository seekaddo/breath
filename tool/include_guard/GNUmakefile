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


$(target) : main$(object_file_suffix) macro_name$(object_file_suffix) entropy_source$(object_file_suffix) subrange_max$(object_file_suffix)
	$(link_to_exec)


macro_name$(object_file_suffix): macro_name.cpp \
 $(root)/tool/include_guard/macro_name.hpp \
 $(root)/breath/random/entropy_source.hpp \
 $(root)/breath/exception/exception.hpp \
 $(root)/breath/random/subrange_adaptor.hpp \
 $(root)/breath/random/subrange_max.hpp

 
main$(object_file_suffix): main.cpp $(root)/breath/random/entropy_source.hpp \
 $(root)/breath/exception/exception.hpp \
 $(root)/tool/include_guard/macro_name.hpp


entropy_source$(object_file_suffix) :      ../../breath/random/entropy_source.cpp
	$(compile_to_object)


subrange_max$(object_file_suffix) : ../../breath/random/subrange_max.cpp
	$(compile_to_object)

main$(object_file_suffix) : main.cpp
	$(compile_to_object)

macro_name$(object_file_suffix) : macro_name.cpp
	$(compile_to_object)

