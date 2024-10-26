#pragma once

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
 * @file mpi_host_communicator_backend.hpp
 * @author Oier Lauzirika Zarrabeitia (oierlauzi@bizkaia.eu)
 * @brief Definition of the compute::mpi_host_communicator_backend class
 * @date 2024-10-26
 * 
 */

#include <xmipp4/core/compute/host_communicator_backend.hpp>

#include <memory>

#include <mpi/mpi.h>

namespace xmipp4 
{
namespace compute
{

class mpi_host_communicator_backend final
    : public host_communicator_backend
{
public:
    mpi_host_communicator_backend() = default;
    mpi_host_communicator_backend(const mpi_host_communicator_backend &other) = delete;
    mpi_host_communicator_backend(mpi_host_communicator_backend &&other) = delete;
    virtual ~mpi_host_communicator_backend() = default;

    mpi_host_communicator_backend& operator=(const mpi_host_communicator_backend &other) = delete;
    mpi_host_communicator_backend& operator=(mpi_host_communicator_backend &&other) = delete;

    const std::string& get_name() const noexcept override;
    version get_version() const noexcept override;
    bool is_available() const noexcept override;
    std::shared_ptr<host_communicator> get_world_communicator() const override;

private:

};

} // namespace compute
} // namespace xmipp4
