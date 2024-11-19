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
 * @file mpi_communicator_backend.hpp
 * @author Oier Lauzirika Zarrabeitia (oierlauzi@bizkaia.eu)
 * @brief Definition of the communication::mpi_communicator_backend class
 * @date 2024-10-26
 * 
 */

#include <xmipp4/core/communication/communicator_backend.hpp>

#include <memory>

#include <mpi.h>

namespace xmipp4 
{
namespace communication
{

class mpi_communicator;

class mpi_communicator_backend final
    : public communicator_backend
{
public:
    const std::string& get_name() const noexcept override;
    version get_version() const noexcept override;
    bool is_available() const noexcept override;
    std::shared_ptr<communicator> get_world_communicator() const override;

private:
    static const std::string m_name;

};

} // namespace communication
} // namespace xmipp4
