// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <xmipp4/core/platform/constexpr.hpp>
#include <xmipp4/core/memory/byte.hpp>

#include <mpi.h>

namespace xmipp4
{
namespace communication
{

template <typename T>
struct mpi_type;

template <>
struct mpi_type<memory::byte>
{
    static MPI_Datatype value() noexcept
    {
        return MPI_BYTE;
    }
};

template <>
struct mpi_type<char>
{
    static MPI_Datatype value() noexcept
    {
        return MPI_CHAR;
    }
};

template <>
struct mpi_type<signed char>
{
    static MPI_Datatype value() noexcept
    {
        return MPI_SIGNED_CHAR;
    }
};

template <>
struct mpi_type<unsigned char>
{
    static MPI_Datatype value() noexcept
    {
        return MPI_UNSIGNED_CHAR;
    }
};

template <>
struct mpi_type<short>
{
    static MPI_Datatype value() noexcept
    {
        return MPI_SHORT;
    }
};

template <>
struct mpi_type<unsigned short>
{
    static MPI_Datatype value() noexcept
    {
        return MPI_UNSIGNED_SHORT;
    }
};

template <>
struct mpi_type<int>
{
    static MPI_Datatype value() noexcept
    {
        return MPI_INT;
    }
};

template <>
struct mpi_type<unsigned int>
{
    static MPI_Datatype value() noexcept
    {
        return MPI_UNSIGNED;
    }
};

template <>
struct mpi_type<long>
{
    static MPI_Datatype value() noexcept
    {
        return MPI_LONG;
    }
};

template <>
struct mpi_type<unsigned long>
{
    static MPI_Datatype value() noexcept
    {
        return MPI_UNSIGNED_LONG;
    }
};

template <>
struct mpi_type<long long>
{
    static MPI_Datatype value() noexcept
    {
        return MPI_LONG_LONG;
    }
};

template <>
struct mpi_type<unsigned long long>
{
    static MPI_Datatype value() noexcept
    {
        return MPI_UNSIGNED_LONG_LONG;
    }
};

template <>
struct mpi_type<float>
{
    static MPI_Datatype value() noexcept
    {
        return MPI_FLOAT;
    }
};

template <>
struct mpi_type<double>
{
    static MPI_Datatype value() noexcept
    {
        return MPI_DOUBLE;
    }
};

template <>
struct mpi_type<long double>
{
    static MPI_Datatype value() noexcept
    {
        return MPI_LONG_DOUBLE;
    }
};

} // namespace communication
} // namespace xmipp4
