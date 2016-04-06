// Copyright 2008-2013 Gennaro Prota
//
// Released under: see license file.
//
// NUOVO FILE: meglio suddividere ---gps

#include "tool/include_guard/macro_name.hpp"
#include "breath/diagnostics/assert.hpp"
#include "breath/random/entropy_source.hpp"

#include <cstddef>
#include <string>

namespace {

std::string
make_random_alnum( int length, breath::entropy_source & source )
{
    std::string const   alnum   = "0123456789"
                                  "abcdefghijklmnopqrstuvwxyz"
                                  "ABCDEFGHIJKLMNOPQRSTUVWXYZ" ;

    std::string         result ;

    if ( length > 0 ) {
        // Reserve in advance, to avoid consuming entropy in the (admittedly
        // unlikely) case that we can't append into the string after a part
        // of the characters has been added and thus we have consumed some
        // entropy
        //
        result.reserve( length ) ;

        int                 count = length ;
        std::size_t         m = alnum.length() - 1 ;
        while ( count > 0 ) {
            result.push_back( alnum[ source( m ) ] ) ;
            -- count ;
        }
    }

    return result ;
}

}


std::string
make_macro_name( std::string const & prefix,
                 int random_part_length,
                 macro_name_creation::exit_status * exit_status )
{
    int const           total_length = prefix.length() + random_part_length ;
    BREATH_ASSERT( total_length > 0
        && total_length <= 63 /* minimum required by C99 */ ) ;

    *exit_status = macro_name_creation::ok ;

    breath::entropy_source
                        source ;
    std::string const   str = make_random_alnum ( random_part_length, source ) ;

    if ( ! source.release() ) {
        *exit_status = macro_name_creation::could_not_release_entropy_source ;
    }

    return prefix + str ;
}
