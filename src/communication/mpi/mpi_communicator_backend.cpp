// SPDX-License-Identifier: GPL-3.0-only

#include "mpi_communicator_backend.hpp"

#include "mpi_instance.hpp"
#include "mpi_communicator.hpp"

#include <xmipp4/core/communication/communicator_manager.hpp>

namespace xmipp4 
{
namespace communication
{

std::string mpi_communicator_backend::get_name() const noexcept
{
    return "mpi";
}

version mpi_communicator_backend::get_version() const noexcept
{
    return mpi_instance::get_mpi_version();
}

bool mpi_communicator_backend::is_available() const noexcept
{
    bool result;

    try
    {
        const auto world_size = 
            get_instance().get_world_communicator()->get_size();

        result = (world_size > 1);
    }
    catch(...)
    {
        result = false;
    }
    
    return result;
}

backend_priority mpi_communicator_backend::get_priority() const noexcept
{
    return backend_priority::normal;
}

std::shared_ptr<communicator> 
mpi_communicator_backend::create_world_communicator() const
{
    return get_instance().get_world_communicator();
}

bool mpi_communicator_backend::register_at(communicator_manager &manager)
{
    return manager.register_backend(std::make_unique<mpi_communicator_backend>());
}


mpi_instance& mpi_communicator_backend::get_instance() const
{
    if (!m_instance)
    {
        m_instance = mpi_instance::get();
    }

    XMIPP4_ASSERT(m_instance);
    return *m_instance;
}

} // namespace communication
} // namespace xmipp4
