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
 * @file mpi_instance.cpp
 * @author Oier Lauzirika Zarrabeitia (oierlauzi@bizkaia.eu)
 * @brief Implementation of mpi_instance.hpp
 * @date 2024-10-26
 * 
 */

#include "mpi_instance.hpp"

#include <xmipp4/core/platform/assert.hpp>

#include <mpi.h>

namespace xmipp4 
{
namespace communication
{

std::weak_ptr<mpi_instance> mpi_instance::m_singleton;

mpi_instance::mpi_instance()
{
    MPI_Init(nullptr, nullptr);
}

mpi_instance::~mpi_instance()
{
    MPI_Finalize();
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

} // namespace communication
} // namespace xmipp4
