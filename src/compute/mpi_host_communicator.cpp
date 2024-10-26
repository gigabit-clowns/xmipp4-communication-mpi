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
 * @file mpi_host_communicator.cpp
 * @author Oier Lauzirika Zarrabeitia (oierlauzi@bizkaia.eu)
 * @brief Implementation of mpi_host_communicator.hpp
 * @date 2024-10-26
 * 
 */

#include "mpi_host_communicator.hpp"

namespace xmipp4 
{
namespace compute
{

mpi_host_communicator::mpi_host_communicator() noexcept
    : mpi_host_communicator(MPI_COMM_NULL)
{
}

mpi_host_communicator::mpi_host_communicator(MPI_Comm mpi_communicator) noexcept
    : m_communicator(mpi_communicator)
{
}

mpi_host_communicator::mpi_host_communicator(mpi_host_communicator &&other) noexcept
    : m_communicator(other.m_communicator)
{
    other.m_communicator = MPI_COMM_NULL;
}

mpi_host_communicator::~mpi_host_communicator()
{
    reset();
}

mpi_host_communicator& 
mpi_host_communicator::operator=(mpi_host_communicator &&other) noexcept
{
    swap(other);
    other.reset();
    return *this;
}

void mpi_host_communicator::reset() noexcept
{
    if (m_communicator != MPI_COMM_NULL && m_communicator != MPI_COMM_WORLD)
    {
        MPI_Comm_free(&m_communicator);
    }
    m_communicator = MPI_COMM_NULL;
}

void mpi_host_communicator::swap(mpi_host_communicator &other) noexcept
{
    std::swap(m_communicator, other.m_communicator);
}

std::size_t mpi_host_communicator::get_size() const
{
    int result;
    
    const auto error = MPI_Comm_size(m_communicator, &result);
    check(error);

    return result;
}

int mpi_host_communicator::get_rank() const
{
    int result;
    
    const auto error = MPI_Comm_rank(m_communicator, &result);
    check(error);

    return result;
}

std::unique_ptr<host_communicator> 
mpi_host_communicator::split(int colour, 
                             int rank_priority ) const
{
    MPI_Comm new_communicator;

    const auto error = MPI_Comm_split(
        m_communicator,
        colour, rank_priority,
        &new_communicator
    );
    check(error);

    try
    {
        return std::make_unique<mpi_host_communicator>(new_communicator);
    }
    catch(...)
    {
        // Error ocurred creating a the new communicator.
        // Free the resources before propagating the error.
        MPI_Comm_free(&new_communicator);
        throw;
    }
}

std::shared_ptr<host_communicator> 
mpi_host_communicator::split_shared(int colour, 
                                    int rank_priority ) const
{
    MPI_Comm new_communicator;

    const auto error = MPI_Comm_split(
        m_communicator,
        colour, rank_priority,
        &new_communicator
    );
    check(error);

    try
    {
        return std::make_shared<mpi_host_communicator>(new_communicator);
    }
    catch(...)
    {
        // Error ocurred creating a the new communicator.
        // Free the resources before propagating the error.
        MPI_Comm_free(&new_communicator);
        throw;
    }
}


void mpi_host_communicator::barrier()
{
    const auto error = MPI_Barrier(m_communicator);
    check(error);
}





void mpi_host_communicator::check(int error)
{
    if (error != MPI_SUCCESS)
    {
        char message[MPI_MAX_ERROR_STRING];
        int count = 0;
        MPI_Error_string(error, message, &count);
        throw std::runtime_error(message);
    }
}

} // namespace compute
} // namespace xmipp4
