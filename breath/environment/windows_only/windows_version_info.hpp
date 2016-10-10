// =========================================================================
//                       Copyright 2007 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________
//
//!     \file
//!     \brief Microsoft Windows version information.
// -------------------------------------------------------------------------

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
    //! Construct a \c windows_version_info object.
    // -----------------------------------------------------------------------
                        windows_version_info() ;

    //! Compiler-generated copy members.
    // -----------------------------------------------------------------------
                        windows_version_info( windows_version_info const & ) =
                                                                    default ;
    windows_version_info &
                        operator=( windows_version_info const & ) = default ;

    //! \return The major version number of the operating system.
    // -----------------------------------------------------------------------
    int                 major_version() const ;

    //! \return The minor version number of the operating system.
    // -----------------------------------------------------------------------
    int                 minor_version() const ;

    //! \return The build number of the operating system.
    // -----------------------------------------------------------------------
    int                 build_number() const ;

    //! \return A (possibly empty) string with the edition of the operating
    //!         system.
    // -----------------------------------------------------------------------
    char const *        edition() const ;

    //! \return The platform of the operating system.
    // -----------------------------------------------------------------------
    os_platform         platform() const ;

    //! \return The member \c wSuiteMask of \c OSVERSIONINFOEX.
    int                 suite_mask() const ;

    //! \return Whether the OS is 64-bit.
    // -----------------------------------------------------------------------
    static bool         is_64_bit() ;

    //! \return Whether the system is of workstation type (Windows Vista,
    //!         XP Professional, etc.).
    // -----------------------------------------------------------------------
    bool                is_workstation() const ;

    //! \return Whether the bit VER_SUITE_WH_SERVER is enabled in wSuiteMask.
    // -----------------------------------------------------------------------
    bool                is_suite_wh_server() const ;

    //! \return Whether the bit VER_SUITE_STORAGE_SERVER is enabled in
    //!         wSuiteMask.
    // -----------------------------------------------------------------------
    bool                is_suite_storage_server() const ;

    //! \return A string with the service pack of the operating system.
    // -----------------------------------------------------------------------
    char const *        service_pack_string() const ;
} ;

}
// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
