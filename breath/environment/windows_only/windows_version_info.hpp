// =========================================================================
//                    Copyright 2007-2016 Gennaro Prota
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
#include <string>
// gps aggiungere, in ANNOUNCE.txt, cosa facciamo con i platform headers
#undef UNICODE
#include <windows.h>
#include <lm.h>


namespace breath {

class windows_version_info
{
private:
    WKSTA_INFO_100 *    m_info = nullptr ;

public:
    //! Constructs a \c windows_version_info object.
    // -----------------------------------------------------------------------
                        windows_version_info() ;

    //! Destroys a \c windows_version_info object.
    // -----------------------------------------------------------------------
                        ~windows_version_info() ;

    //! Deleted copy members.
    // -----------------------------------------------------------------------
                        windows_version_info( windows_version_info const & ) =
                                                                    delete ;
    windows_version_info &
                        operator=( windows_version_info const & ) = delete ;

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
    //!         system. The return type could be <code>maybe< std::string >
    //!         </code> but I didn't want to introduce another dependency.
    // -----------------------------------------------------------------------
    std::string         edition() const ;

    //! \return Whether the OS is 64-bit.
    // -----------------------------------------------------------------------
    static bool         is_64_bit() ;

    //! \return Whether the OS is a Windows client version.
    // -----------------------------------------------------------------------
    static bool         is_client() ;

    //! \return A string with the service pack of the operating system.
    // -----------------------------------------------------------------------
    static std::string  service_pack_string() ;
} ;

}
// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
