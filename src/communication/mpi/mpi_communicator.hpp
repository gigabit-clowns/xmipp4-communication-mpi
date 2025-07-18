// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <xmipp4/core/communication/communicator.hpp>
#include <xmipp4/core/span.hpp>
#include <xmipp4/core/memory/byte.hpp>

#include <memory>

#include <mpi.h>

namespace xmipp4 
{
namespace communication
{

namespace detail
{

template<typename Comm, typename... Ts>
class mpi_communicator_helper;

template<typename Comm, typename T, typename... Ts>
class mpi_communicator_helper<Comm, T, Ts...>
    : public mpi_communicator_helper<Comm, Ts...>
{
public:
    using mpi_communicator_helper<Comm, Ts...>::send;
    using mpi_communicator_helper<Comm, Ts...>::receive;
    using mpi_communicator_helper<Comm, Ts...>::send_receive;
    using mpi_communicator_helper<Comm, Ts...>::broadcast;
    using mpi_communicator_helper<Comm, Ts...>::scatter;
    using mpi_communicator_helper<Comm, Ts...>::gather;
    using mpi_communicator_helper<Comm, Ts...>::all_gather;
    using mpi_communicator_helper<Comm, Ts...>::reduce;
    using mpi_communicator_helper<Comm, Ts...>::all_reduce;
    using mpi_communicator_helper<Comm, Ts...>::all_to_all;

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
class mpi_communicator_helper<Comm>
    : public communicator
{
};

} // namespace detail





class mpi_communicator final
    : public detail::mpi_communicator_helper<mpi_communicator, 
                                                  memory::byte,
                                                  char,
                                                  signed char,
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
    mpi_communicator() noexcept;
    explicit mpi_communicator(MPI_Comm mpi_communicator) noexcept;
    mpi_communicator(const mpi_communicator &other) = delete;
    mpi_communicator(mpi_communicator &&other) noexcept;
    ~mpi_communicator() override;

    mpi_communicator& operator=(const mpi_communicator &other) = delete;
    mpi_communicator& operator=(mpi_communicator &&other) noexcept;

    MPI_Comm get_handle() noexcept;

    void reset() noexcept;
    void swap(mpi_communicator &other) noexcept;

    std::size_t get_size() const override;

    int get_rank() const override;

    std::shared_ptr<communicator> split(int colour, 
                                        int rank_priority ) const override;

    void barrier() override;

private:
    MPI_Comm m_communicator;

};

} // namespace communication
} // namespace xmipp4
