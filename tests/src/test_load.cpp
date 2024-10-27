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
 * @file test_version.cpp
 * @author Oier Lauzirika Zarrabeitia (oierlauzi@bizkaia.eu)
 * @brief Test for version.hpp
 * @date 2023-08-12
 */


#include <catch2/catch_test_macros.hpp>

#include <xmipp4/core/interface_registry.hpp>
#include <xmipp4/core/plugin_manager.hpp>
#include <xmipp4/core/plugin.hpp>
#include <xmipp4/core/compute/host_communicator_backend.hpp>
#include <xmipp4/core/compute/host_communicator_manager.hpp>

using namespace xmipp4;


TEST_CASE( "load and register xmipp4-compute-mpi plugin", "[compute-mpi]" ) 
{
    plugin_manager manager;

    
    const auto* mpi_plugin = 
        manager.load_plugin("../libxmipp4-compute-mpi.so");
    REQUIRE( mpi_plugin != nullptr );
    REQUIRE( mpi_plugin->get_name() == "xmipp4-compute-mpi" );

    interface_registry interfaces;
    mpi_plugin->register_at(interfaces);

    auto *mpi_backend =
        interfaces.get_interface_manager<compute::host_communicator_manager>()
        .get_backend("mpi");
    REQUIRE( mpi_backend != nullptr );
    REQUIRE( mpi_backend->get_name() == "mpi" );

}