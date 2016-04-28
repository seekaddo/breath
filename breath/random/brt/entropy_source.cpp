// =========================================================================
//                    Copyright 2008-2015 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________


#include "breath/random/entropy_source.hpp"
#include "breath/random/subrange_adaptor.hpp"
#include "breath/porting/dependent_code.hpp"
#include BREATH_DEPENDENT_CODE( system, entropy_source.cpp )
#include "breath/preprocessing/prevent_macro_expansion.hpp"

#include <cstring>

namespace breath {

entropy_source::entropy_source()
    :   m_impl( new impl )
{
}

entropy_source::~entropy_source() noexcept
{
    delete m_impl ;
}

entropy_source::result_type
entropy_source::next()
{
    return m_impl->next() ;
}

bool
entropy_source::release()
{
    return m_impl->release() ;
}

entropy_source::result_type
entropy_source::min BREATH_PREVENT_MACRO_EXPANSION ()
{
    return m_impl->minimum() ;
}

entropy_source::result_type
entropy_source::max BREATH_PREVENT_MACRO_EXPANSION ()
{
    return m_impl->maximum() ;
}

entropy_source::result_type
entropy_source::operator()()
{
    return next() ;
}

entropy_source::result_type
entropy_source::operator()( result_type maximum )
{
    subrange_adaptor< entropy_source >
                        adaptor( *this, maximum ) ;
    return adaptor.next() ;
}

entropy_source::exception::
exception( std::string const & msg ) throw()
{
    std::strncpy( &m_message[ 0 ], msg.c_str(), max_length ) ;
}

char const *
entropy_source::exception::what() const throw()
{
    return m_message ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
