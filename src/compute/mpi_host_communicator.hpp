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

#include <mpi.h>

namespace xmipp4 
{
namespace compute
{

namespace detail
{

template<typename Comm, typename... Ts>
class mpi_host_communicator_helper;

template<typename Comm, typename T, typename... Ts>
class mpi_host_communicator_helper<Comm, T, Ts...>
    : public mpi_host_communicator_helper<Comm, Ts...>
{
public:
    mpi_host_communicator_helper() = default;
    mpi_host_communicator_helper(const mpi_host_communicator_helper &other) = default;
    mpi_host_communicator_helper(mpi_host_communicator_helper &&other) = default;
    virtual ~mpi_host_communicator_helper() = default;

    mpi_host_communicator_helper& operator=(const mpi_host_communicator_helper &other) = default;
    mpi_host_communicator_helper& operator=(mpi_host_communicator_helper &&other) = default;

    using mpi_host_communicator_helper<Comm, Ts...>::send;
    using mpi_host_communicator_helper<Comm, Ts...>::receive;
    using mpi_host_communicator_helper<Comm, Ts...>::send_receive;
    using mpi_host_communicator_helper<Comm, Ts...>::broadcast;
    using mpi_host_communicator_helper<Comm, Ts...>::scatter;
    using mpi_host_communicator_helper<Comm, Ts...>::gather;
    using mpi_host_communicator_helper<Comm, Ts...>::all_gather;
    using mpi_host_communicator_helper<Comm, Ts...>::reduce;
    using mpi_host_communicator_helper<Comm, Ts...>::all_reduce;
    using mpi_host_communicator_helper<Comm, Ts...>::all_to_all;

    void send(int destination_rank, span<const T> buf) final;

    std::size_t receive(int source_rank, span<T> buf) final;

    std::size_t send_receive(int destination_rank, span<const T> send_buf,
                             int source_rank, span<T> receive_buf ) final;

    void broadcast(int root, span<T> buf) final;

    void scatter(int root, 
                 span<const T> send_buf, span<T> recv_buf ) final;

    void gather(int root, 
                span<const T> send_buf, span<T> recv_buf ) final;

    void all_gather(span<const T> send_buf, span<T> recv_buf) final;

    void reduce(int root, reduction_operation op,
                span<const T> send_buf, span<T> recv_buf ) final;

    void all_reduce(reduction_operation op,
                    span<const T> send_buf, span<T> recv_buf ) final;

    void all_to_all(span<const T> send_buf, span<T> recv_buf) final;

private:
    int get_rank() const;
    MPI_Comm get_communicator() noexcept;

};

template<typename Comm>
class mpi_host_communicator_helper<Comm>
    : public host_communicator
{
public:
    mpi_host_communicator_helper() = default;
    mpi_host_communicator_helper(const mpi_host_communicator_helper &other) = default;
    mpi_host_communicator_helper(mpi_host_communicator_helper &&other) = default;
    virtual ~mpi_host_communicator_helper() = default;

    mpi_host_communicator_helper& operator=(const mpi_host_communicator_helper &other) = default;
    mpi_host_communicator_helper& operator=(mpi_host_communicator_helper &&other) = default;

};

} // namespace detail





class mpi_host_communicator final
    : public detail::mpi_host_communicator_helper<mpi_host_communicator, 
                                                  memory::byte,
                                                  char,
                                                  unsigned char,
                                                  short,
                                                  unsigned short,
                                                  int,
                                                  unsigned int,
                                                  long,
                                                  unsigned long,
                                                  long long,
                                                  unsigned long long,
                                                  float,
                                                  double,
                                                  long double>
{
public:
    mpi_host_communicator() noexcept;
    mpi_host_communicator(MPI_Comm mpi_communicator) noexcept;
    mpi_host_communicator(const mpi_host_communicator &other) = delete;
    mpi_host_communicator(mpi_host_communicator &&other) noexcept;
    virtual ~mpi_host_communicator();

    mpi_host_communicator& operator=(const mpi_host_communicator &other) = delete;
    mpi_host_communicator& operator=(mpi_host_communicator &&other) noexcept;

    MPI_Comm get_handle() noexcept;

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

};

} // namespace compute
} // namespace xmipp4
