// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <xmipp4/core/reduction_operation.hpp>

#include <mpi.h>

namespace xmipp4
{
namespace communication
{

MPI_Op to_mpi(reduction_operation op) noexcept;

} // namespace communication
} // namespace xmipp4
