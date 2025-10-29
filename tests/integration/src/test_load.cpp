// SPDX-License-Identifier: GPL-3.0-only

#include <catch2/catch_test_macros.hpp>

#include <xmipp4/core/service_catalog.hpp>
#include <xmipp4/core/plugin_manager.hpp>
#include <xmipp4/core/plugin.hpp>
#include <xmipp4/core/communication/communicator_manager.hpp>
#include <xmipp4/core/platform/operating_system.h>

using namespace xmipp4;


static std::string get_mpi_plugin_path()
{
    #if XMIPP4_WINDOWS
        return "xmipp4-communication-mpi.dll";
    #elif XMIPP4_APPLE || XMIPP4_LINUX
        return "./libxmipp4-communication-mpi.so";
    #else
        #error "Unknown platform"
    #endif
}

TEST_CASE( "load and register xmipp4-communication-mpi plugin", "[communication-mpi]" ) 
{
    plugin_manager manager;

    const auto* mpi_plugin = 
        manager.load_plugin(get_mpi_plugin_path());

    REQUIRE( mpi_plugin != nullptr );
    REQUIRE( mpi_plugin->get_name() == "xmipp4-communication-mpi" );

    service_catalog interfaces;
    mpi_plugin->register_at(interfaces);

    auto *mpi_backend =
        interfaces.get_service_manager<communication::communicator_manager>()
        .get_backend("mpi");
    REQUIRE( mpi_backend != nullptr );
    REQUIRE( mpi_backend->get_name() == "mpi" );
}
