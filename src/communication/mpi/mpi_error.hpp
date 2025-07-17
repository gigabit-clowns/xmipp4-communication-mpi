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

#include <stdexcept>

namespace xmipp4
{
namespace communication
{

/**
 * @brief Exception class representing a MPI error.
 * 
 */
class mpi_error
    : public std::runtime_error
{
    using runtime_error::runtime_error;
};

/**
 * @brief Check the return code of an MPI function
 * 
 * If the error code is MPI_SUCCESSFUL this function does nothing.
 * Otherwise it throws an exception with the appropiate message.
 * 
 * @param error_code Error code returned by MPI
 */
void mpi_check_error(int error_code);

} // namespace communication
} // namespace xmipp4
