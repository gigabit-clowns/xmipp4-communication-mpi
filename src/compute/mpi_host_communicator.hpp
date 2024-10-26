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
 * @file mpi_host_communicator.hpp
 * @author Oier Lauzirika Zarrabeitia (oierlauzi@bizkaia.eu)
 * @brief Definition of the compute::mpi_host_communicator class
 * @date 2024-10-26
 * 
 */

#include <xmipp4/core/compute/host_communicator.hpp>
#include <xmipp4/core/compute/reduction_operation.hpp>
#include <xmipp4/core/span.hpp>
#include <xmipp4/core/memory/byte.hpp>

#include <memory>

#include <mpi/mpi.h>

namespace xmipp4 
{
namespace compute
{

class mpi_host_communicator
    : public host_communicator
{
public:
    mpi_host_communicator() noexcept;
    mpi_host_communicator(MPI_Comm mpi_communicator) noexcept;
    mpi_host_communicator(const mpi_host_communicator &other) = delete;
    mpi_host_communicator(mpi_host_communicator &&other) noexcept;
    virtual ~mpi_host_communicator();

    mpi_host_communicator& operator=(const mpi_host_communicator &other) = delete;
    mpi_host_communicator& operator=(mpi_host_communicator &&other) noexcept;

    void reset() noexcept;
    void swap(mpi_host_communicator &other) noexcept;

    std::size_t get_size() const override;

    int get_rank() const override;

    std::unique_ptr<host_communicator> split(int colour, 
                                             int rank_priority ) const override;

    std::shared_ptr<host_communicator> split_shared(int colour, 
                                                    int rank_priority ) const override;


    void barrier() override;

private:
    MPI_Comm m_communicator;

    static void check(int error);

};

} // namespace compute
} // namespace xmipp4
