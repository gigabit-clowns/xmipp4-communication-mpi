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

#include "mpi_instance.hpp"

#include "mpi_error.hpp"

#include <xmipp4/core/platform/assert.hpp>

#include <mpi.h>

namespace xmipp4 
{
namespace communication
{

std::weak_ptr<mpi_instance> mpi_instance::m_singleton;

mpi_instance::mpi_instance()
{
    const auto error = MPI_Init(nullptr, nullptr);
    mpi_check_error(error);
    
    m_world = std::make_shared<mpi_communicator>(MPI_COMM_WORLD);
}

mpi_instance::~mpi_instance()
{
    MPI_Finalize();
}

const std::shared_ptr<mpi_communicator>& 
mpi_instance::get_world_communicator() const noexcept
{
    return m_world;
}

std::shared_ptr<mpi_instance> mpi_instance::get()
{
    auto result = m_singleton.lock();

    if(!result)
    {
        result.reset(new mpi_instance());
        m_singleton = result;
    }

    XMIPP4_ASSERT(result);
    return result;

}

version mpi_instance::get_mpi_version()
{
    int major = 0;
    int minor = 0;
    MPI_Get_version(&major, &minor); // Does not require initialization
    return version(major, minor, 0);
}

} // namespace communication
} // namespace xmipp4
