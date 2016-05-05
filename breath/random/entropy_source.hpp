// =========================================================================
//                    Copyright 2008-2015 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#ifndef BREATH_GUARD_zRk6qVzrOdWWtkjYcUpuIkpnrRj8cg0q
#define BREATH_GUARD_zRk6qVzrOdWWtkjYcUpuIkpnrRj8cg0q

#include "breath/idiom/declare_non_copyable.hpp"
#include "breath/diagnostics/exception.hpp"

#include <string>

namespace breath {

//      NOTE: this class is designed to be usable with random_shuffle
//            and shuffle. (This is, BTW, why it has members named "min"
//            and "max", which I generally avoid, given how many sources
//            define them as macro names.)
//
//      It satisfies the requirements of a "uniform random number
//      generator".
//
//      What about the complexity of g()? [gps]
//
// ---------------------------------------------------------------------------
class entropy_source {

    BREATH_DECLARE_NON_COPYABLE( entropy_source )

public:
//!         note that the system entropy source may work on a
//!         smaller type (typically unsigned char); we don't
//!         use unsigned char here on the interface because we
//!         we don't want things such as std::cout << rnd.next()
//!         to output a character instead of a number
// ---------------------------------------------------------------------------
    typedef unsigned int
                        result_type ;
    class               exception ;
public:
                        entropy_source() ;
                        ~entropy_source() noexcept ;


    //!     Returns the next random value. Each call gives (with
    //!     overwhelming probability) a different value
    //!------------------------------------------------------------------------
    result_type         next() ;

    result_type         min() noexcept ;
    result_type         max() noexcept ;

    //!     TODO:
    //!         define entropy()??? It should be 8 for /dev/random... what
    //!         about the CryptoAPI?
    // ------------------------------------------------------------------------
    result_type         operator()() ;
    result_type         operator()( result_type maximum ) ;


    //      Releases system resources associated with this object
    //      (usually a file or a handle)
    //
    //      Returns true <=> the resource(s) were successfully
    //      released.
    //
    //      Throws: nothing (reports via its return value)
    //
    //      NOTE: you cannot reattempt a release if it has already
    //            succeeded.
    // ------------------------------------------------------------------------
    bool                release() noexcept ;

private:
    class               impl ;
    impl * const        m_impl ;
} ;

class entropy_source::exception : public virtual breath::exception
{
public:
    static void         raise( std::string const & message ) ;
    
    explicit            exception( std::string const & msg ) noexcept ;
    virtual char const *
                        what() const noexcept ;
private:
    enum { max_length = 4 * 1024 } ;
    char                m_message[ max_length ] ;
} ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
