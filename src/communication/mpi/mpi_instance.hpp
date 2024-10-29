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
 * @file mpi_instance.hpp
 * @author Oier Lauzirika Zarrabeitia (oierlauzi@bizkaia.eu)
 * @brief Provides the communication::mpi_instance class.
 * @date 2024-10-26
 * 
 */

#include <memory>

namespace xmipp4 
{
namespace communication
{

class mpi_instance
{
public:
    mpi_instance(const mpi_instance &other) = delete;
    mpi_instance(mpi_instance &&other) = delete;
    ~mpi_instance();

    mpi_instance& operator=(const mpi_instance &other) = delete;
    mpi_instance& operator=(mpi_instance &&other) = delete;

    static mpi_instance& get();

private:
    static std::unique_ptr<mpi_instance> m_singleton;
    
    mpi_instance();

};

} // namespace communication
} // namespace xmipp4
