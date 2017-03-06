// =========================================================================
//                    Copyright 2007-2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________
//
//!     \file
//!     \brief Microsoft Windows version information.
// -------------------------------------------------------------------------

#include "breath/idiom/declare_non_copyable.hpp"
#include <string>

namespace breath {

class windows_version_info
{
public:
    //! Constructs a \c windows_version_info object.
    // -----------------------------------------------------------------------
                        windows_version_info() ;

    //! Destroys a \c windows_version_info object.
    // -----------------------------------------------------------------------
                        ~windows_version_info() noexcept ;

    //! Deleted copy members.
    // -----------------------------------------------------------------------
    BREATH_DECLARE_NON_COPYABLE( windows_version_info )

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

    //! \return A (possibly empty) string with the service pack of the
    //!         operating system. This could use <code>maybe< std::string >
    //!         </code> as well.
    // -----------------------------------------------------------------------
    static std::string  service_pack_string() ;

private:
    // This uses the pimpl idiom to avoid including <Windows.h> from here.
    //
    class               impl ;
    impl * const        m_impl ;
} ;

}
// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
