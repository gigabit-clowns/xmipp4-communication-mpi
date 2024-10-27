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
 * @file mpi_host_communicator_backend.cpp
 * @author Oier Lauzirika Zarrabeitia (oierlauzi@bizkaia.eu)
 * @brief Implementation of mpi_host_communicator_backend.hpp
 * @date 2024-10-26
 * 
 */

#include "mpi_host_communicator_backend.hpp"

#include "mpi_instance.hpp"
#include "mpi_host_communicator.hpp"

#include <mpi/mpi.h>

namespace xmipp4 
{
namespace compute
{

const std::string& mpi_host_communicator_backend::get_name() const noexcept
{
    static const std::string name = "mpi";
    return name;
}

version mpi_host_communicator_backend::get_version() const noexcept
{
    int major = 0;
    int minor = 0;
    MPI_Get_version(&major, &minor);
    return version(major, minor, 0);
}

bool mpi_host_communicator_backend::is_available() const noexcept
{
    return true;
}

std::shared_ptr<host_communicator> 
mpi_host_communicator_backend::get_world_communicator() const
{
    mpi_instance::get(); // Ensure MPI is initialized
    return std::make_shared<mpi_host_communicator>(MPI_COMM_WORLD);
}

} // namespace compute
} // namespace xmipp4
