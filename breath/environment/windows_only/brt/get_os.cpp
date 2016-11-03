// =========================================================================
//                    Copyright 2007-2015 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________
//
//      get_os()
//      ========
//
//      Windows-specific implementation
//
//
//      Necessary background:
//      ---------------------
//
//      The bizzarre design and "evolution" of the Windows API makes
//      the whole task of getting the running OS version a fastidious
//      programming puzzle, and an accurate analysis is in order
//      before attempting a reusable implementation. First, two API
//      functions exist for the purpose: GetVersion() and
//      GetVersionEx(), with the latter being available (as of April
//      2007, and presumably ever) on all Windows flavours except NT
//      3.1. Given the current low diffusion of this latter Windows we
//      give up its support and always use GetVersionEx().
//
//      From now on, we assume that you have read the documentation of
//      GetVersionEx(), OSVERSIONINFO and OSVERSIONINFOEX. You have
//      likely immediately noticed from the MS docs, that different
//      Windows versions exist sharing the same version number:
//
//      Operating system               Version number
//
//       Windows Server "Longhorn"      6.0
//       Windows Vista                  6.0
//
//       Windows XP Professional x64    5.2
//       Windows Server 2003 R2         5.2
//       Windows Server 2003            5.2
//
//       Windows XP                     5.1
//       Windows 2000                   5.0
//
// ---------------------------------------------------------------------------
//      Here's a simple tree-like diagram deducible from the
//      OSVERSIONINFOEX documentation:
//
// major              4                        5                      6
//             /    /    \    \            /   |   \
// minor      0    10    90    \          0    1    2                 0
//           .   Win98  WinMe  ...       ...  XP   XP Pro x64       Vista
//                                                 or 2003 R2    or "Longhorn"
//           |\                                    or 2003
// Platf.    | \
//  Id      WIN NT                      PLAT_NT
//          |   |
//          95  NT 4.0                  2000 ??????? po' esse NT??? (gps)
//
//                                                              [ Diagram 1 ]
// ---------------------------------------------------------------------------
//
//      Note that, not only the pair (major, minor) isn't sufficient
//      to determine what OS is running --which we already knew-- but,
//      even adding dwPlatformId, indecisions remain (5.2 and 6.0
//      branches).
//
//      In effect, not even *all* the members of OSVERSIONINFOEX are
//      (always) enough: we need, depending on the case, either
//      wProductType, member of OSVERSIONINFOEX, or a call to
//      ::GetSystemMetrics [sic] or a call to ::GetSystemInfo, as
//      sketched in pseudo-code below:
//
//         // not supported (yet)
//         if version > 6.0
//             [FUTURE]
//
//         // Vista / Server "Longhorn"
//         if version == 6.0
//             if wProductType == VER_NT_WORKSTATION
//                 "Windows Vista"
//             else
//                 "Windows Server \"Longhorn\""
//
//         // XP Professional x64 Edition / Server 2003 R2 / Server 2003
//         if version == 5.2
//             if ::GetSystemInfo() == x64 and wProductType == NT_WORKSTATION
//                 "Windows XP Professional x64 Edition"
//             else if ( ::GetSystemMetrics( SM_SERVERR2 ) ) != 0
//                 "Windows Server 2003 R2"
//             else
//                 "Windows Server 2003"
//
//         else
//             // see [ Diagram 1 ]
//             5.1      XP
//             5.0      2000
//             ...      ...
//
//
// ===========================================================================
//
// Once you have figured out the version of the operating system that is
// running, you can attack the details:
//
//    Detected OS        95      98                  Me            All others
//    CSDVersion        " C"    " A"                 ??
//                      OSR2   Second Edition   additional info   service pack
// ---------------------------------------------------------------------------
//
// Further details can be gathered by examining the wSuiteMask member of
// the OSVERSIONEX info structure (not available on...) and/or querying specific
// registry values. This is basically all trivial switch-case like stuff and
// doesn't really need a diagram.
//
//                          NT 4                        2000        XP      2003
//    SuiteMask
// (   only in
// OSVERSIONINFOEX )          1            3                    PERSONAL    DATACENTER
//                                                                      [*]
//                        Workstation   Server                   |Home Ed.|   dc
//
// (note the initial space in " C" and " A")
//
// [*] Server 2003 editions:
//      switch( SuiteMask )
//        case DATACENTER: "Datacenter Edition" break ;
//        case ENTERPRISE: "Enterprise Edition" break ;
//        case BLADE:      "Web Edition"        break ;
//        default:         "Standard Edition"   break ;
//
// Limitations:
//  For simplicity sake we avoid the following detections:
//
//    * Specific edition for Windows NT 4.0 SP6 and later
//      (NT Workstation: Workstation, Home Edition, Professional)
//      (NT Server:      Datacenter Edition, Enterprise Edition, Web Edition, Standard Edition)

#include "breath/environment/windows_only/get_os.hpp"

#include "breath/diagnostics/assert.hpp"
#include "breath/environment/windows_only/windows_version_info.hpp"
#include "breath/environment/windows_only/os_platform.hpp"
#include "breath/environment/windows_only/os_id.hpp"


namespace breath {
namespace        {

constexpr unsigned
win_version( int major, int minor )
{
    return major * 256u + minor ;
}

bool
is_server_2003_r2()
{
    // define the sm_* constant ourselves, for now, to avoid requiring
    // the latest SDK headers [FUTURE]
    int const sm_serverr2( 89 ) ;
    return 0 != ::GetSystemMetrics( sm_serverr2 ) ;
}

// Precondition:  never call this for Windows NT 3.5 or earlier (see MS docs)
bool
is_x64()
{
    // despite the "AMD64" in the macro name, this actually tests for x64
    // (AMD or Intel); --also, as perplexing as it may be, the docs make
    // no mention of any possible failure of GetSystemInfo...
    SYSTEM_INFO si = {} ;
    ::GetSystemInfo( &si ) ;
    return si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 ;
}

os_id
identify_nt( windows_version_info const & info )
{
    os_id           id( os_id::windows_unknown ) ;
    unsigned const version(
             win_version( info.major_version(), info.minor_version() ) ) ;

    switch( version )
    {
    case win_version( 10, 0 ):
        id = os_id::windows_10 ;
        break ;
    case win_version( 6, 3 ):
        id = os_id::windows_8_1 ;
        break ;
    case win_version( 6, 2 ):
        id = os_id::windows_8 ;
        break ;

    case win_version( 6, 1 ):
        if ( info.is_workstation() ) {
            id = os_id::windows_7 ;
        } else {
            id = os_id::windows_server_2008_r2 ;
        }
        break ;
    case win_version( 6, 0 ):
        if( info.is_workstation() ) {
            id = os_id::windows_vista ;
        } else {
            id = os_id::windows_server_2008 ;
        }
        break ;

    case win_version( 5, 2 ):
        if( is_server_2003_r2() ) {
            id = os_id::windows_server_2003_r2 ;
        }
        else if( info.is_workstation() ) {
            if( is_x64() ) {
                id = os_id::windows_xp_professional_x64_edition ;
            }
        }
        if ( info.is_suite_wh_server() ) {
            id = os_id::windows_home_server ;
        } else if ( info.is_suite_storage_server() ) {
            id = os_id::windows_storage_server_2003 ;
        } else {
            id = os_id::windows_server_2003 ;
        }
        break ;

    case win_version( 5, 1 ):
        id = os_id::windows_xp ;
        break ;

    case win_version( 5, 0 ):
        id = os_id::windows_2000 ;
        break ;

    case win_version( 4, 0 ):
        id = os_id::windows_nt ;
        break ;

    default:
        // hmm... new version on the shelves?
        id = os_id::windows_unknown ;
        break ;
    }

    return id ;
}

os_id
identify_9x( windows_version_info const & info )
{
    unsigned const version(
        win_version( info.major_version(), info.minor_version() ) ) ;

    switch( version )
    {
        case win_version( 4, 90 ):
            return os_id::windows_me ;
            break ;

        case win_version( 4, 10 ):
            return os_id::windows_98 ;
            break ;

        case win_version( 4, 0 ):
            return os_id::windows_95 ;
            break ;
    }

    // shouldn't happen; they didn't produce a new OS in the 9x family, did
    // they?
    BREATH_ASSERT( false ) ;
    return os_id::windows_unknown ;
}
}

os_id
get_os()
{
    windows_version_info const
                        info ;
    os_platform const & platform( info.platform() ) ;

    if(      platform == os_platform::windows_nt )
        return identify_nt( info ) ;
    else if( platform == os_platform::windows_9x )
        return identify_9x( info ) ;
    else if( platform == os_platform::win32s )
        return os_id::win32s ;
    else
        return os_id::windows_unknown ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
