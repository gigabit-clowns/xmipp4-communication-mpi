/***************************************************************************
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307  USA
 *
 *  All comments concerning this program package may be sent to the
 *  e-mail address 'xmipp@cnb.csic.es'
 ***************************************************************************/

#include "mpi_plugin.hpp"
#include "communication/mpi/mpi_communicator_backend.hpp"

#include <xmipp4/core/interface_catalog.hpp>
#include <xmipp4/core/communication/communicator_manager.hpp>

namespace xmipp4 
{

const std::string mpi_plugin::name = "xmipp4-communication-mpi";

const std::string& mpi_plugin::get_name() const noexcept
{
    return name; 
}

version mpi_plugin::get_version() const noexcept
{
    return version(
        VERSION_MAJOR,
        VERSION_MINOR,
        VERSION_PATCH
    );
}

void mpi_plugin::register_at(interface_catalog& catalog) const
{
    auto& communicator_manager = 
        catalog.get_backend_manager<communication::communicator_manager>();
    
    communication::mpi_communicator_backend::register_at(communicator_manager);
}

} // namespace xmipp4
