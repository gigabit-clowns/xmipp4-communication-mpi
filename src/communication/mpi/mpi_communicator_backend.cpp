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

#include "mpi_communicator_backend.hpp"

#include "mpi_instance.hpp"
#include "mpi_communicator.hpp"

#include <xmipp4/core/communication/communicator_manager.hpp>

namespace xmipp4 
{
namespace communication
{

std::string mpi_communicator_backend::get_name() const noexcept
{
    return "mpi";
}

version mpi_communicator_backend::get_version() const noexcept
{
    return mpi_instance::get_mpi_version();
}

bool mpi_communicator_backend::is_available() const noexcept
{
    bool result;

    try
    {
        const auto world_size = 
            get_instance().get_world_communicator()->get_size();

        result = (world_size > 1);
    }
    catch(...)
    {
        result = false;
    }
    
    return result;
}

backend_priority mpi_communicator_backend::get_priority() const noexcept
{
    return backend_priority::normal;
}

std::shared_ptr<communicator> 
mpi_communicator_backend::create_world_communicator() const
{
    return get_instance().get_world_communicator();
}

bool mpi_communicator_backend::register_at(communicator_manager &manager)
{
    return manager.register_backend(std::make_unique<mpi_communicator_backend>());
}


mpi_instance& mpi_communicator_backend::get_instance() const
{
    if (!m_instance)
    {
        m_instance = mpi_instance::get();
    }

    XMIPP4_ASSERT(m_instance);
    return *m_instance;
}

} // namespace communication
} // namespace xmipp4
