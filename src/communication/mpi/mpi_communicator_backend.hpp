// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "mpi_instance.hpp"

#include <xmipp4/core/communication/communicator_backend.hpp>

#include <memory>

#include <mpi.h>

namespace xmipp4 
{
namespace communication
{

class communicator_manager;
class mpi_communicator;

class mpi_communicator_backend final
    : public communicator_backend
{
public:
    mpi_communicator_backend() = default;
    mpi_communicator_backend(const mpi_communicator_backend &other) = default;
    mpi_communicator_backend(mpi_communicator_backend &&other) = default;
    ~mpi_communicator_backend() override = default;

    mpi_communicator_backend&
    operator=(const mpi_communicator_backend &other) = default;
    mpi_communicator_backend&
    operator=(mpi_communicator_backend &&other) = default;

    std::string get_name() const noexcept override;
    version get_version() const noexcept override;
    bool is_available() const noexcept override;
    backend_priority get_priority() const noexcept override;
    std::shared_ptr<communicator> create_world_communicator() const override;

    static bool register_at(communicator_manager &manager);

private:
    mutable std::shared_ptr<mpi_instance> m_instance;

    mpi_instance& get_instance() const;

};

} // namespace communication
} // namespace xmipp4
