#pragma once

#include "SharedPointer.hpp"
#include "precice/impl/Participant.hpp"
#include "precice/impl/SharedPointer.hpp"
#include "mesh/SharedPointer.hpp"
#include "cplscheme/SharedPointer.hpp"
#include "mapping/SharedPointer.hpp"
#include "m2n/M2N.hpp"
#include "m2n/config/M2NConfiguration.hpp"
#include "logging/Logger.hpp"
#include "xml/XMLTag.hpp"
#include <string>
#include "boost/smart_ptr.hpp"

namespace precice {
namespace config {

/**
 * @brief Configures class SolverInterfaceImpl from XML.
 */
class SolverInterfaceConfiguration : public xml::XMLTag::Listener
{
public:

  /**
   * @brief Constructor.
   */
  SolverInterfaceConfiguration(xml::XMLTag& parent);

  /**
   * @brief Destructor.
   *
   * Deletes geometry configuration and coupling scheme configuration.
   */
  virtual ~SolverInterfaceConfiguration() {}

  /**
   * @brief Callback method required when using xml::XMLTag.
   */
  virtual void xmlTagCallback ( xml::XMLTag& callingTag );

  /**
   * @brief Callback method required when using xml::XMLTag.
   */
  virtual void xmlEndTagCallback ( xml::XMLTag& callingTag );

  /**
   * @brief Returns number of spatial dimensions configured.
   */
  int getDimensions() const;

  const mesh::PtrDataConfiguration getDataConfiguration() const
  {
    return _dataConfiguration;
  }

  const mesh::PtrMeshConfiguration getMeshConfiguration() const
  {
    return _meshConfiguration;
  }

  const m2n::M2NConfiguration::SharedPointer getM2NConfiguration() const
  {
    return _m2nConfiguration;
  }

  const PtrParticipantConfiguration& getParticipantConfiguration() const;

  const cplscheme::PtrCouplingSchemeConfiguration
  getCouplingSchemeConfiguration() const
  {
    return _couplingSchemeConfiguration;
  }

  /**
   * @brief For manual configuration in test cases.
   */
  void setDataConfiguration ( mesh::PtrDataConfiguration config )
  {
    _dataConfiguration = config;
  }

  /**
   * @brief For manual configuration in test cases.
   */
  void setMeshConfiguration ( mesh::PtrMeshConfiguration config )
  {
    _meshConfiguration = config;
  }

  /**
    * @brief For manual configuration in test cases.
    */
   void setParticipantConfiguration ( PtrParticipantConfiguration config )
   {
     _participantConfiguration = config;
   }

private:

  // @brief Logging device.
  static logging::Logger _log;

  // Tag and subtag names used within this configuration.
  const std::string TAG;
  const std::string ATTR_DIMENSIONS;
  
  // @brief Spatial dimension of problem to be solved. Either 2 or 3.
  int _dimensions;

  // @brief Participating solvers in the coupled simulation.
  //std::vector<impl::PtrParticipant> _participants;

  // @brief Index (in _participants) of solver accessing the interface.
  //int _indexAccessor;

  mesh::PtrDataConfiguration _dataConfiguration;

  mesh::PtrMeshConfiguration _meshConfiguration;

  m2n::M2NConfiguration::SharedPointer _m2nConfiguration;

  PtrParticipantConfiguration _participantConfiguration;

  cplscheme::PtrCouplingSchemeConfiguration _couplingSchemeConfiguration;
};

}} // namespace precice, config
