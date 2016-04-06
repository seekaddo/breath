// Copyright 2008-2013 Gennaro Prota
//
// Released under: see license file.
//
// NUOVO FILE: meglio suddividere ---gps

#include <string>

class macro_name_creation // this could be a scoped enum in C++11
{
public:
    enum exit_status { ok, could_not_release_entropy_source } ;
} ;

std::string         make_macro_name( std::string const & prefix,
                                     int random_part_length,
                                     macro_name_creation::exit_status * ) ;
