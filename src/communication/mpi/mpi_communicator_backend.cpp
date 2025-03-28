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

/**
 * @file mpi_communicator_backend.cpp
 * @author Oier Lauzirika Zarrabeitia (oierlauzi@bizkaia.eu)
 * @brief Implementation of mpi_communicator_backend.hpp
 * @date 2024-10-26
 * 
 */

#include "mpi_communicator_backend.hpp"

#include "mpi_instance.hpp"
#include "mpi_communicator.hpp"

#include <mpi.h>

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
    int major = 0;
    int minor = 0;
    MPI_Get_version(&major, &minor); // Does not require initialization
    return version(major, minor, 0);
}

bool mpi_communicator_backend::is_available() const noexcept
{
    try
    {
        initialize();
    }
    catch(...)
    {
        return false;
    }
    
    int size = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    return size > 1;
}

backend_priority mpi_communicator_backend::get_priority() const noexcept
{
    return backend_priority::normal;
}

std::shared_ptr<communicator> 
mpi_communicator_backend::create_world_communicator() const
{
    initialize();
    return std::make_shared<mpi_communicator>(MPI_COMM_WORLD);
}



void mpi_communicator_backend::initialize() const
{
    if (!m_instance)
    {
        m_instance = mpi_instance::get();
    }

    XMIPP4_ASSERT(m_instance);
}

} // namespace communication
} // namespace xmipp4
