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
 * @file mpi_communicator.cpp
 * @author Oier Lauzirika Zarrabeitia (oierlauzi@bizkaia.eu)
 * @brief Implementation of mpi_communicator.hpp
 * @date 2024-10-26
 * 
 */

#include "mpi_communicator.hpp"

#include "mpi_error.hpp"
#include "mpi_type.hpp"
#include "mpi_operation.hpp"

#include <stdexcept>

namespace xmipp4 
{
namespace communication
{
namespace detail
{

static std::size_t require_same_count(std::size_t send_count, 
                                      std::size_t recv_count )
{
    if (send_count != recv_count)
    {
        throw std::invalid_argument(
            "send and receive buffer sizes must match"
        );
    }

    return send_count;
}

template<typename Comm, typename T, typename... Ts>
void mpi_communicator_helper<Comm, T, Ts...>::send(int destination_rank, 
                                                   span<const T> buf )
{
    const auto error = MPI_Send(
        buf.data(), static_cast<int>(buf.size()), mpi_type<T>::value(), 
        destination_rank, 0, get_communicator()
    );
    mpi_check_error(error);
}

template<typename Comm, typename T, typename... Ts>
std::size_t 
mpi_communicator_helper<Comm, T, Ts...>::receive(int source_rank, 
                                                 span<T> buf)
{
    MPI_Status status;
    const auto error = MPI_Recv(
        buf.data(), static_cast<int>(buf.size()), mpi_type<T>::value(),
        source_rank, 0, 
        get_communicator(), &status
    );
    mpi_check_error(error);

    int count;
    MPI_Get_count(&status, mpi_type<T>::value(), &count);
    return count;
}

template<typename Comm, typename T, typename... Ts>
std::size_t 
mpi_communicator_helper<Comm, T, Ts...>::send_receive(int destination_rank, 
                                                      span<const T> send_buf,
                                                      int source_rank, 
                                                      span<T> receive_buf )
{
    MPI_Status status;
    const auto error = MPI_Sendrecv(
        send_buf.data(), static_cast<int>(send_buf.size()), mpi_type<T>::value(),
        destination_rank, 0,
        receive_buf.data(), static_cast<int>(receive_buf.size()), mpi_type<T>::value(),
        source_rank, 0, 
        get_communicator(), &status
    );
    mpi_check_error(error);

    int count;
    MPI_Get_count(&status, mpi_type<T>::value(), &count);
    return count;
}

template<typename Comm, typename T, typename... Ts>
void mpi_communicator_helper<Comm, T, Ts...>::broadcast(int root, span<T> buf)
{
    const auto error = MPI_Bcast(
        buf.data(), static_cast<int>(buf.size()), mpi_type<T>::value(), root,
        get_communicator()

    );
    mpi_check_error(error);
}

template<typename Comm, typename T, typename... Ts>
void mpi_communicator_helper<Comm, T, Ts...>::scatter(int root, 
                                                      span<const T> send_buf, 
                                                      span<T> recv_buf )
{
    int error;
    if(send_buf.data() == recv_buf.data() && root == get_rank())
    {
        error = MPI_Scatter(
            send_buf.data(), static_cast<int>(send_buf.size()), mpi_type<T>::value(),
            MPI_IN_PLACE, static_cast<int>(recv_buf.size()), mpi_type<T>::value(),
            root, get_communicator()
        );
    }
    else
    {
        error = MPI_Scatter(
            send_buf.data(), static_cast<int>(send_buf.size()), mpi_type<T>::value(),
            recv_buf.data(), static_cast<int>(recv_buf.size()), mpi_type<T>::value(),
            root, get_communicator()
        );
    }
    mpi_check_error(error);
}

template<typename Comm, typename T, typename... Ts>
void mpi_communicator_helper<Comm, T, Ts...>::gather(int root, 
                                                     span<const T> send_buf, 
                                                     span<T> recv_buf )
{
    int error;
    if(send_buf.data() == recv_buf.data() && root == get_rank())
    {
        error = MPI_Gather(
            MPI_IN_PLACE, static_cast<int>(send_buf.size()), mpi_type<T>::value(),
            recv_buf.data(), static_cast<int>(recv_buf.size()), mpi_type<T>::value(),
            root, get_communicator()
        );
    }
    else
    {
        error = MPI_Gather(
            send_buf.data(), static_cast<int>(send_buf.size()), mpi_type<T>::value(),
            recv_buf.data(), static_cast<int>(recv_buf.size()), mpi_type<T>::value(),
            root, get_communicator()
        );
    }
    mpi_check_error(error);
}

template<typename Comm, typename T, typename... Ts>
void mpi_communicator_helper<Comm, T, Ts...>::all_gather(span<const T> send_buf, 
                                                         span<T> recv_buf )
{
    int error;
    if(send_buf.data() == recv_buf.data())
    {
        error = MPI_Allgather(
            MPI_IN_PLACE, static_cast<int>(send_buf.size()), mpi_type<T>::value(),
            recv_buf.data(), static_cast<int>(recv_buf.size()), mpi_type<T>::value(),
            get_communicator()
        );
    }
    else
    {
        error = MPI_Allgather(
            send_buf.data(), static_cast<int>(send_buf.size()), mpi_type<T>::value(),
            recv_buf.data(), static_cast<int>(recv_buf.size()), mpi_type<T>::value(),
            get_communicator()
        );
    }
    mpi_check_error(error);
}

template<typename Comm, typename T, typename... Ts>
void mpi_communicator_helper<Comm, T, Ts...>::reduce(int root, 
                                                     reduction_operation op,
                                                     span<const T> send_buf, 
                                                     span<T> recv_buf )
{
    const auto size = require_same_count(send_buf.size(), recv_buf.size());

    int error;
    if(send_buf.data() == recv_buf.data() && root == get_rank())
    {
        error = MPI_Reduce(
            MPI_IN_PLACE, recv_buf.data(), static_cast<int>(size), 
            mpi_type<T>::value(), to_mpi(op), root, get_communicator()
        );
    }
    else
    {
        error = MPI_Reduce(
            send_buf.data(), recv_buf.data(), static_cast<int>(size), 
            mpi_type<T>::value(), to_mpi(op), root, get_communicator()
        );
    }
    mpi_check_error(error);
}

template<typename Comm, typename T, typename... Ts>
void mpi_communicator_helper<Comm, T, Ts...>::all_reduce(reduction_operation op,
                                                         span<const T> send_buf, 
                                                         span<T> recv_buf )
{
    const auto size = require_same_count(send_buf.size(), recv_buf.size());

    int error;
    if(send_buf.data() == recv_buf.data())
    {
        error = MPI_Allreduce(
            MPI_IN_PLACE, recv_buf.data(), static_cast<int>(size), 
            mpi_type<T>::value(), to_mpi(op), get_communicator()
        );
    }
    else
    {
        error = MPI_Allreduce(
            send_buf.data(), recv_buf.data(), static_cast<int>(size), 
            mpi_type<T>::value(), to_mpi(op), get_communicator()
        );
    }
    mpi_check_error(error);

}

template<typename Comm, typename T, typename... Ts>
void mpi_communicator_helper<Comm, T, Ts...>::all_to_all(span<const T> send_buf, 
                                                         span<T> recv_buf )
{
    int error;
    if(send_buf.data() == recv_buf.data())
    {
        error = MPI_Alltoall(
            MPI_IN_PLACE, static_cast<int>(send_buf.size()), mpi_type<T>::value(),
            recv_buf.data(), static_cast<int>(recv_buf.size()), mpi_type<T>::value(),
            get_communicator()
        );
    }
    else
    {
        error = MPI_Alltoall(
            send_buf.data(), static_cast<int>(send_buf.size()), mpi_type<T>::value(),
            recv_buf.data(), static_cast<int>(recv_buf.size()), mpi_type<T>::value(),
            get_communicator()
        );
    }
    mpi_check_error(error);
}

template<typename Comm, typename T, typename... Ts>
int mpi_communicator_helper<Comm, T, Ts...>::get_rank() const
{
    return static_cast<const Comm*>(this)->get_rank();
}

template<typename Comm, typename T, typename... Ts>
MPI_Comm mpi_communicator_helper<Comm, T, Ts...>::get_communicator() noexcept
{
    return static_cast<Comm*>(this)->get_handle();
}

} // namespace detail





mpi_communicator::mpi_communicator() noexcept
    : mpi_communicator(MPI_COMM_NULL)
{
}

mpi_communicator::mpi_communicator(MPI_Comm mpi_communicator) noexcept
    : m_communicator(mpi_communicator)
{
}

mpi_communicator::mpi_communicator(mpi_communicator &&other) noexcept
    : m_communicator(other.m_communicator)
{
    other.m_communicator = MPI_COMM_NULL;
}

mpi_communicator::~mpi_communicator()
{
    reset();
}

mpi_communicator& 
mpi_communicator::operator=(mpi_communicator &&other) noexcept
{
    swap(other);
    other.reset();
    return *this;
}
    
MPI_Comm mpi_communicator::get_handle() noexcept
{
    return m_communicator;   
}

void mpi_communicator::reset() noexcept
{
    if (m_communicator != MPI_COMM_NULL && m_communicator != MPI_COMM_WORLD)
    {
        MPI_Comm_free(&m_communicator);
    }
    m_communicator = MPI_COMM_NULL;
}

void mpi_communicator::swap(mpi_communicator &other) noexcept
{
    std::swap(m_communicator, other.m_communicator);
}

std::size_t mpi_communicator::get_size() const
{
    int result;
    
    const auto error = MPI_Comm_size(m_communicator, &result);
    mpi_check_error(error);

    return result;
}

int mpi_communicator::get_rank() const
{
    int result;
    
    const auto error = MPI_Comm_rank(m_communicator, &result);
    mpi_check_error(error);

    return result;
}

std::unique_ptr<communicator> 
mpi_communicator::split(int colour, 
                        int rank_priority ) const
{
    MPI_Comm new_communicator;

    const auto error = MPI_Comm_split(
        m_communicator,
        colour, rank_priority,
        &new_communicator
    );
    mpi_check_error(error);

    try
    {
        return std::make_unique<mpi_communicator>(new_communicator);
    }
    catch(...)
    {
        // Error ocurred creating a the new communicator.
        // Free the resources before propagating the error.
        MPI_Comm_free(&new_communicator);
        throw;
    }
}

std::shared_ptr<communicator> 
mpi_communicator::split_shared(int colour, 
                               int rank_priority ) const
{
    MPI_Comm new_communicator;

    const auto error = MPI_Comm_split(
        m_communicator,
        colour, rank_priority,
        &new_communicator
    );
    mpi_check_error(error);

    try
    {
        return std::make_shared<mpi_communicator>(new_communicator);
    }
    catch(...)
    {
        // Error ocurred creating a the new communicator.
        // Free the resources before propagating the error.
        MPI_Comm_free(&new_communicator);
        throw;
    }
}


void mpi_communicator::barrier()
{
    const auto error = MPI_Barrier(m_communicator);
    mpi_check_error(error);
}

} // namespace communication
} // namespace xmipp4
