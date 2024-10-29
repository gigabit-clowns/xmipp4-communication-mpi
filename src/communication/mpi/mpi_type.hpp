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
 * @file mpi_type.hpp
 * @author Oier Lauzirika Zarrabeitia (oierlauzi@bizkaia.eu)
 * @brief Type conversions for MPI
 * @date 2024-10-26
 * 
 */

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
