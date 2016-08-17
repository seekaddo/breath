// =========================================================================
//                       Copyright 2007 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include <ostream>
// gps aggiungere, in ANNOUNCE.txt, cosa facciamo con i platform headers
#undef UNICODE
#include <windows.h>


namespace breath {

class os_platform;

class windows_version_info
{
private:
    typedef OSVERSIONINFOEX 
                        extended_type ;
    typedef OSVERSIONINFO
                        simple_type ;

    extended_type       m_api_info ;

    template< typename APIStruct >
    bool                retrieve() ;

public:
                        windows_version_info() ;
    // compiler-generated copy

    int                 major_version() const ;
    int                 minor_version() const ;
    int                 build_number() const ;
    char const *        edition() const ;
    os_platform         platform() const ;

    int                 suite_mask() const ;

    static bool         is_64_bit() ;
    bool                is_workstation() const ;
    bool                is_suite_wh_server() const ;
    bool                is_suite_storage_server() const ;

    char const *        service_pack_string() const ;
} ;

}
// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
