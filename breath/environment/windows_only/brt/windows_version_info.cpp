// =========================================================================
//                    Copyright 2007-2015 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/environment/windows_only/windows_version_info.hpp"
#include "breath/environment/windows_only/os_platform.hpp"

#include <stdexcept>

namespace breath {

// using a bool for failure/success isn't stellar software engineering, and
// wouldn't be acceptable in a public component, but given that this is an
// implementation detail, and that it gives some conciseness...
template< typename ApiStruct >
bool
windows_version_info::retrieve()
{
    int const           failure( 0 ) ;

    m_api_info.dwOSVersionInfoSize = sizeof( ApiStruct ) ;
    return failure != ::GetVersionEx(
                        reinterpret_cast< simple_type * >( &m_api_info )
                        ) ;
}

windows_version_info::windows_version_info()
    : m_api_info()
{
    if ( !retrieve< extended_type >() && !retrieve< simple_type >() ) {
            // gps we'll probably have something more specific here
        throw std::runtime_error( "cannot retrieve Windows version info" ) ;
    }
}

int
windows_version_info::major_version() const
{
    return m_api_info.dwMajorVersion ;
}

int
windows_version_info::minor_version() const
{
    return m_api_info.dwMinorVersion ;
}

int
windows_version_info::build_number() const
{
    // This is a bit tricky: the documentation of OSVERSIONINFO
    // says that
    //
    // a) for Me/98/95 we have to consider the low-order word only
    //
    // b) For other systems, or when we are not using the old
    //    OSVERSIONINFO structure, we have to consider the whole
    //    dword (so, there could theoretically be build numbers
    //    higher than 65535)
    //
    // Now, some experiment on Windows XP, with the exe in Win95,
    // 98, Me compatibility-mode, showed that even if the system
    // reports to be, say, Windows 98, it still allows to use
    // OSVERSIONINFOEX. But, since we can be sure that on any of
    // Me/98/95 the build number is all contained in the low-order
    // word, we can simply omit to test whether we used
    // OSVERSIONINFO or a newer structure.
    //
    // As further annotation: we use platform == windows_9x as a
    // shortcut for "is in { Me, 98, 95 }". Strictly speaking we
    // should do the latter test, but that requires get_os(); in
    // practice the shortcut is safe as it's very unlikely that
    // new Windows versions will be introduced which belong to the
    // Win9x family.
    //
    // gps cast DWORD -> int Ok? :-/
    // -------------------------------------------------------------------

    DWORD const n( m_api_info.dwBuildNumber );
    return platform() == os_platform::windows_9x
        ? LOWORD( n )
        : n
        ;
}

char const *
windows_version_info::edition() const
{
    // GetProductInfo() works only when major_version() >= 6.
    if( major_version() < 6 ) {
        return "" ;
    }

    DWORD               dw ;
    GetProductInfo( major_version(), minor_version(), 0, 0, &dw ) ;

    switch( dw ) {
        case PRODUCT_UNDEFINED:
            return "<undefined>" ;
            break ;
        case PRODUCT_ULTIMATE:
            return "Ultimate Edition" ;
            break ;
        case PRODUCT_HOME_BASIC:
            return "Home Basic Edition" ;
            break ;
        case PRODUCT_HOME_PREMIUM:
            return "Home Premium Edition" ;
            break ;
        case PRODUCT_ENTERPRISE:
            return "Enterprise Edition" ;
            break ;
        case PRODUCT_HOME_BASIC_N:
            return "Home Basic N" ;
            break ;
        case PRODUCT_BUSINESS:
            return "Business Edition" ;
            break ;
        case PRODUCT_STANDARD_SERVER:
            return "Standard Edition" ;
            break ;
        case PRODUCT_DATACENTER_SERVER:
            return "Datacenter Edition" ;
            break ;
       case PRODUCT_SMALLBUSINESS_SERVER:
            return "Small Business Server" ;
            break ;
        case PRODUCT_ENTERPRISE_SERVER:
            return "Server Enterprise (full installation)" ;
            break ;
        case PRODUCT_STARTER:
            return "Starter" ;
            break ;
        case PRODUCT_DATACENTER_SERVER_CORE:
            return "Server Datacenter (core installation)" ;
            break ;
        case PRODUCT_STANDARD_SERVER_CORE:
            return "Server Standard (core installation)" ;
            break ;
        case PRODUCT_ENTERPRISE_SERVER_CORE:
            return "Server Enterprise (core installation)" ;
            break ;
        case PRODUCT_ENTERPRISE_SERVER_IA64:
            return "Server Enterprise for Itanium-based Systems" ;
            break ;
        case PRODUCT_BUSINESS_N:
            return "Business N" ;
            break ;
        case PRODUCT_WEB_SERVER:
            return "Web Server (full installation)" ;
            break ;
        case PRODUCT_CLUSTER_SERVER:
            return "HPC Edition" ;
            break ;
        case PRODUCT_HOME_SERVER:
            return "Home Server" ; // gps undocumented in my SDK
            break ;
        case PRODUCT_STORAGE_EXPRESS_SERVER:
            return "Storage Server Express" ;
            break ;
        case PRODUCT_STORAGE_STANDARD_SERVER:
            return "Storage Server Standard" ;
            break ;
        case PRODUCT_STORAGE_WORKGROUP_SERVER:
            return "Storage Server Workgroup" ;
            break ;
        case PRODUCT_STORAGE_ENTERPRISE_SERVER:
            return "Storage Server Enterprise" ;
            break ;
        case PRODUCT_SERVER_FOR_SMALLBUSINESS:
            return "for Windows Essential Server Solutions" ;
            break ;
        case PRODUCT_SMALLBUSINESS_SERVER_PREMIUM: // gps undocumented in my SDK
            return "Small Business Server Premium" ;
            break ;
        case PRODUCT_HOME_PREMIUM_N:
            return "Home Premium N" ;
            break ;
        case PRODUCT_ENTERPRISE_N:
            return "Enterprise N" ;
            break ;
        case PRODUCT_ULTIMATE_N:
            return "Ultimate N" ;
            break ;
        case PRODUCT_WEB_SERVER_CORE:
            return "Web Server (core installation)" ;
            break ;
        case PRODUCT_MEDIUMBUSINESS_SERVER_MANAGEMENT:
            return "Essential Business Server Management Server" ;
            break ;
        case PRODUCT_MEDIUMBUSINESS_SERVER_SECURITY:
            return "Essential Business Server Security Server" ;
            break ;
        case PRODUCT_MEDIUMBUSINESS_SERVER_MESSAGING:
            return "Essential Business Server Messaging Server" ;
            break ;
        case PRODUCT_SERVER_FOUNDATION:
            return "Server Foundation" ;
            break ;
        case PRODUCT_HOME_PREMIUM_SERVER: // gps undocumented in my SDK
            return "Home Premium Server" ;
            break ;
        case PRODUCT_SERVER_FOR_SMALLBUSINESS_V:
            return "without Hyper-V for Windows Essential Server Solutions" ;
            break ;
        case PRODUCT_STANDARD_SERVER_V:
            return "Server Standard without Hyper-V (full installation)" ;
            break ;
        case PRODUCT_DATACENTER_SERVER_V:
            return "Server Datacenter without Hyper-V (full installation)" ;
            break ;
        case PRODUCT_ENTERPRISE_SERVER_V:
            return "Server Enterprise without Hyper-V (full installation)" ;
            break ;
        case PRODUCT_DATACENTER_SERVER_CORE_V:
            return "Server Datacenter without Hyper-V (core installation)" ;
            break ;
        case PRODUCT_STANDARD_SERVER_CORE_V:
            return "" ;
            break ;
        case PRODUCT_ENTERPRISE_SERVER_CORE_V:
            return"Server Enterprise without Hyper-V (core installation)" ;
        case PRODUCT_HYPERV:
            return "Microsoft Hyper-V Server" ;
            break ;
        case PRODUCT_STORAGE_EXPRESS_SERVER_CORE: // gps undocumented in my SDK
            return "Storage Server Express (core installation)" ;
            break ;
        case PRODUCT_STORAGE_STANDARD_SERVER_CORE: // gps undocumented in my SDK
            return "Storage Server Standard (core installation)" ;
            break ;
        case PRODUCT_STORAGE_WORKGROUP_SERVER_CORE: // gps undocumented in my SDK
            return "Storage Server Workgroup (core installation)" ;
        case PRODUCT_STORAGE_ENTERPRISE_SERVER_CORE: // gps undocumented in my SDK
            return "Storage Server Enterprise (core installation)" ;
            break ;
        case PRODUCT_STARTER_N:
            return "Starter N" ;
            break ;
        case PRODUCT_PROFESSIONAL:
            return "Professional" ;
            break ;
        case PRODUCT_PROFESSIONAL_N:
            return "Professional N" ;
            break ;
        case PRODUCT_SB_SOLUTION_SERVER:
            return "undocumented [PRODUCT_SB_SOLUTION_SERVER]" ; //gps [FUTURE]
            break ;
        case PRODUCT_SERVER_FOR_SB_SOLUTIONS: //gps undocumented in my SDK
            return "for Windows Essential Server Solutions" ;
            break ;
        case PRODUCT_STANDARD_SERVER_SOLUTIONS:
            return "undocumented [PRODUCT_STANDARD_SERVER_SOLUTIONS]" ; // gps
            break ;
        case PRODUCT_STANDARD_SERVER_SOLUTIONS_CORE:
            return "undocumented [PRODUCT_STANDARD_SERVER_SOLUTIONS_CORE]" ; // gps
            break ;
        case PRODUCT_SB_SOLUTION_SERVER_EM:
            return "undocumented [PRODUCT_SB_SOLUTION_SERVER_EM]" ; // gps
            break ;
        case PRODUCT_SERVER_FOR_SB_SOLUTIONS_EM:
            return "undocumented [PRODUCT_SERVER_FOR_SB_SOLUTIONS_EM]" ; // gps
            break ;
        case PRODUCT_SOLUTION_EMBEDDEDSERVER:
            return "undocumented [PRODUCT_SOLUTION_EMBEDDEDSERVER]" ; // gps
            break ;
        case PRODUCT_SOLUTION_EMBEDDEDSERVER_CORE:
            return "undocumented [PRODUCT_SOLUTION_EMBEDDEDSERVER_CORE]" ; // gps
            break ;
        case PRODUCT_SMALLBUSINESS_SERVER_PREMIUM_CORE:
            return "undocumented [PRODUCT_SMALLBUSINESS_SERVER_PREMIUM_CORE]" ; //gps
            break ;
        case PRODUCT_ESSENTIALBUSINESS_SERVER_MGMT:
            return "undocumented [PRODUCT_ESSENTIALBUSINESS_SERVER_MGMT]" ; //gps
            break ;
        case PRODUCT_ESSENTIALBUSINESS_SERVER_ADDL:
            return "undocumented [PRODUCT_ESSENTIALBUSINESS_SERVER_ADDL]" ; //gps
            break ;
        case PRODUCT_ESSENTIALBUSINESS_SERVER_MGMTSVC:
            return "undocumented [PRODUCT_ESSENTIALBUSINESS_SERVER_MGMTSVC]" ; // gps
            break ;
        case PRODUCT_ESSENTIALBUSINESS_SERVER_ADDLSVC:
            return "undocumented [PRODUCT_ESSENTIALBUSINESS_SERVER_ADDLSVC]" ; // gps
            break ;
        case PRODUCT_CLUSTER_SERVER_V:
            return "undocumented [PRODUCT_CLUSTER_SERVER_V]" ; // gps
            break ;
        case PRODUCT_EMBEDDED:
            return "undocumented [PRODUCT_EMBEDDED]" ; //gps
            break ;
        case PRODUCT_STARTER_E:
            return "Starter E" ;
            break ;
        case PRODUCT_HOME_BASIC_E:
            return "Home Basic E" ;
            break ;
        case PRODUCT_HOME_PREMIUM_E:
            return "Home Premium E" ;
            break ;
        case PRODUCT_PROFESSIONAL_E:
            return "Professional E  " ;
            break ;
        case PRODUCT_ENTERPRISE_E:
            return "Enterprise E" ;
            break ;
        case PRODUCT_ULTIMATE_E:
            return "Ultimate E" ;
            break ;
        case PRODUCT_UNLICENSED:
            return "*unlicensed*" ;
            break ;

        default:
            return "<unknown edition>" ;
            break ;
    }
}

os_platform
windows_version_info::platform() const
{
    return os_platform( m_api_info.dwPlatformId ) ;
}

int
windows_version_info::suite_mask() const
{
    return m_api_info.wSuiteMask ;
}

bool
windows_version_info::is_64_bit() const
{
    SYSTEM_INFO         si ;
    GetNativeSystemInfo( &si ) ;
    return si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64
        || si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64 ;
}

bool
windows_version_info::is_workstation() const
{
    // note that this will return false when OSVERSIONINFOEX
    // is not available (VER_NT_WORKSTATION is different from 0)
    return m_api_info.wProductType == VER_NT_WORKSTATION ;
}

bool
windows_version_info::is_suite_wh_server() const
{
    // note that this will return false when OSVERSIONINFOEX
    // is not available (VER_SUITE_WH_SERVER is different from 0)
    return ( m_api_info.wSuiteMask & VER_SUITE_WH_SERVER ) != 0 ;
}

bool
windows_version_info::is_suite_storage_server() const
{
    return ( m_api_info.wSuiteMask & VER_SUITE_STORAGE_SERVER ) != 0 ;
}

char const *
windows_version_info::service_pack_string() const
{
    return m_api_info.szCSDVersion ;
}

}
// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:

