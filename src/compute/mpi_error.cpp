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
 * @file mpi_error.cpp
 * @author Oier Lauzirika Zarrabeitia (oierlauzi@bizkaia.eu)
 * @brief Implementation of mpi_error.hpp
 * @date 2024-10-26
 * 
 */

#include "mpi_error.hpp"

#include <mpi/mpi.h>

namespace xmipp4 
{
namespace compute
{

void mpi_check_error(int error_code)
{
    if (error_code != MPI_SUCCESS)
    {
        char message[MPI_MAX_ERROR_STRING];
        int count = 0;
        MPI_Error_string(error, message, &count);
        throw std::runtime_error(message);
    }
}

} // namespace compute
} // namespace xmipp4
