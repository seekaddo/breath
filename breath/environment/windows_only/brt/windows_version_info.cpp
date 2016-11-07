// =========================================================================
//                    Copyright 2007-2015 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/environment/windows_only/windows_version_info.hpp"
#include "breath/text/from_string.hpp"
#include "breath/text/to_string.hpp"

#include <VersionHelpers.h>
#include <stdexcept>
#include <string>

namespace breath {

windows_version_info::windows_version_info()
{
    constexpr int       level = 100 ;
    NET_API_STATUS const
                        status = NetWkstaGetInfo( nullptr, level,
                                     reinterpret_cast< BYTE ** >( &m_info ) ) ;
    if ( status != NERR_Success ) {
        // gps we'll probably have something more specific here
        throw std::runtime_error( "cannot retrieve Windows version info" ) ;
    }
}

windows_version_info::~windows_version_info()
{
    // Ignoring the return value (success or failure).
    NetApiBufferFree( m_info ) ;
}

int
windows_version_info::major_version() const
{
    return m_info->wki100_ver_major ;
}

int
windows_version_info::minor_version() const
{
    return m_info->wki100_ver_minor ;
}

int
windows_version_info::build_number() const
{
    //      Take the Windows build number from the registry.
    //      In my registry there are both CurrentBuild and
    //      CurrentBuildNumber. Using the latter as it has a more
    //      explicit name. [gps]
    // -------------------------------------------------------------------
    HKEY                key = NULL;
    LONG const          ret = RegOpenKeyEx( HKEY_LOCAL_MACHINE,
                              "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion",
                              0,
                              KEY_QUERY_VALUE | KEY_WOW64_32KEY,
                              &key ) ;
    if ( ret != ERROR_SUCCESS ) {
        // gps we'll probably have something more specific here
        throw std::runtime_error( "cannot open the CurrentVersion"
                                  " registry key" ) ;
    }
    constexpr int       size = 256;
    DWORD               dw_size = size ;
    char                buffer[ size ] = {} ;
    int                 ret2 = RegGetValue( key, "", "CurrentBuildNumber",
                                 RRF_RT_ANY, nullptr,
                                 &buffer, &dw_size ) ;
    if ( ret2 != ERROR_SUCCESS ) {
        // gps we'll probably have something more specific here
        throw std::runtime_error( "cannot query the CurrentBuildNumber value"
                                  " from registry" ) ;
    }
    return breath::from_string< int >(std::string( buffer ) ) ;
}

char const *
windows_version_info::edition() const
{
    // GetProductInfo() works only when major_version() >= 6.
    if( major_version() < 6 ) {
        return "" ;
    }

    DWORD               dw ;
    int const           failure = 0 ;
    if ( GetProductInfo( major_version(), minor_version(), 0, 0, &dw ) == failure ) {
        return "" ;
    }

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
            return "Storage Server 2008 R2 Essentials" ;
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
        case PRODUCT_SMALLBUSINESS_SERVER_PREMIUM:
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
        case PRODUCT_HOME_PREMIUM_SERVER:
            return "Home Server 2011" ;
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
        case PRODUCT_STORAGE_EXPRESS_SERVER_CORE:
            return "Storage Server Express (core installation)" ;
            break ;
        case PRODUCT_STORAGE_STANDARD_SERVER_CORE:
            return "Storage Server Standard (core installation)" ;
            break ;
        case PRODUCT_STORAGE_WORKGROUP_SERVER_CORE:
            return "Storage Server Workgroup (core installation)" ;
            break ;
        case PRODUCT_STORAGE_ENTERPRISE_SERVER_CORE:
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
            return "Small Business Server 2011 Essentials" ;
            break ;
        case PRODUCT_SERVER_FOR_SB_SOLUTIONS:
            return "Server For SB Solutions" ;
            break ;
        case PRODUCT_STANDARD_SERVER_SOLUTIONS:
            return "Server Solutions Premium " ;
            break ;
        case PRODUCT_STANDARD_SERVER_SOLUTIONS_CORE:
            return "Server Solutions Premium (core installation)" ;
            break ;
        case PRODUCT_SB_SOLUTION_SERVER_EM:
            return "Server For SB Solutions EM" ;
            break ;
        case PRODUCT_SERVER_FOR_SB_SOLUTIONS_EM:
            return "Server For SB Solutions EM" ;
            break ;
        case PRODUCT_SOLUTION_EMBEDDEDSERVER:
            return "MultiPoint Server" ;
            break ;
        case PRODUCT_SOLUTION_EMBEDDEDSERVER_CORE:
            return "undocumented [PRODUCT_SOLUTION_EMBEDDEDSERVER_CORE]" ; // gps
            break ;
        case PRODUCT_SMALLBUSINESS_SERVER_PREMIUM_CORE:
            return "Small Business Server Premium (core installation)" ;
            break ;
        case PRODUCT_ESSENTIALBUSINESS_SERVER_MGMT:
            return "Essential Server Solution Management" ;
            break ;
        case PRODUCT_ESSENTIALBUSINESS_SERVER_ADDL:
            return "Essential Server Solution Additional" ;
            break ;
        case PRODUCT_ESSENTIALBUSINESS_SERVER_MGMTSVC:
            return "Essential Server Solution Management SVC" ;
            break ;
        case PRODUCT_ESSENTIALBUSINESS_SERVER_ADDLSVC:
            return " Essential Server Solution Additional SVC" ;
            break ;
        case PRODUCT_CLUSTER_SERVER_V:
            return "Server Hyper Core V" ;
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

bool
windows_version_info::is_64_bit()
{
    SYSTEM_INFO         si ;
    GetNativeSystemInfo( &si ) ;
    return si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64
        || si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64 ;
}

bool
windows_version_info::is_client()
{
    // It has no real impact on us, however this function is
    // documented to return a BOOL but declared to return a bool in
    // the corresponding header [last checked: November 2016].
    return IsWindowsServer() == 0 ;
}

std::string
windows_version_info::service_pack_string()
{
    HKEY                key = NULL;
    LONG const          ret = RegOpenKeyEx( HKEY_LOCAL_MACHINE,
                              "SYSTEM\\CurrentControlSet\\Control\\Windows",
                              0,
                              KEY_QUERY_VALUE | KEY_WOW64_32KEY,
                              &key ) ;
    if ( ret != ERROR_SUCCESS ) {
        // gps we'll probably have something more specific here
        throw std::runtime_error( "cannot open the Control\\Windows"
                                  " registry key" ) ;
    }
    DWORD               value ;
    DWORD               dw_size = sizeof value ;
    int                 ret2 = RegGetValue( key, "", "CSDVersion",
                                 RRF_RT_ANY, nullptr,
                                 &value, &dw_size ) ;
    if ( ret2 != ERROR_SUCCESS ) {
        // gps we'll probably have something more specific here
        throw std::runtime_error( "cannot query the CSDVersion value"
                                  " from registry" ) ;
    }

    int const           sp = value / 256 ;
    return sp == 0
        ? ""
        : "Service Pack " + breath::to_string( sp )
        ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:

