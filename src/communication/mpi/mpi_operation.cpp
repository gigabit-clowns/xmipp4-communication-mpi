// SPDX-License-Identifier: GPL-3.0-only

#include "mpi_operation.hpp"

namespace xmipp4 
{
namespace communication
{

MPI_Op to_mpi(reduction_operation op) noexcept
{
    switch (op)
    {
    case reduction_operation::sum: return MPI_SUM;
    case reduction_operation::product: return MPI_PROD;
    case reduction_operation::min: return MPI_MIN;
    case reduction_operation::max: return MPI_MAX;
    default: return MPI_OP_NULL;
    }
}

} // namespace communication
} // namespace xmipp4
