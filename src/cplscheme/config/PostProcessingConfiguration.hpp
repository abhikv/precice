#pragma once

#include "cplscheme/impl/MVQNPostProcessing.hpp"
#include "cplscheme/impl/PostProcessing.hpp"
#include "cplscheme/impl/SharedPointer.hpp"
#include "logging/Logger.hpp"
#include "mesh/SharedPointer.hpp"
#include "precice/config/SharedPointer.hpp"
#include "xml/XMLTag.hpp"

namespace precice
{
namespace cplscheme
{

class PostProcessingConfiguration : public xml::XMLTag::Listener
{
public:
  // @brief Name of the XML tag holding post-processing information.
  //static const std::string& getTag();

  PostProcessingConfiguration(const mesh::PtrMeshConfiguration &meshConfig);

  /// Returns the configured (to be checked by isValid()) coupling scheme.
  impl::PtrPostProcessing getPostProcessing();

  /**
    * @brief Returns a pointer to the PostProcessingConfig object for the coarse model optimization method
    */
  PtrPostProcessingConfiguration getCoarseModelOptimizationConfig();

  /// Callback method required when using xml::XMLTag.
  virtual void xmlTagCallback(xml::XMLTag &callingTag);

  /// Callback method required when using xml::XMLTag.
  virtual void xmlEndTagCallback(xml::XMLTag &callingTag);

  /// Removes configured post-processing.
  void clear();

  /// Connect tags.
  void connectTags(xml::XMLTag &tag);

  std::vector<std::string> &getNeededMeshes()
  {
    return _neededMeshes;
  }

  void setIsAddManifoldMappingTagAllowed(bool b)
  {
    _isAddManifoldMappingTagAllowed = b;
  }

private:
  static logging::Logger _log;

  const std::string TAG;
  const std::string TAG_RELAX;
  const std::string TAG_INIT_RELAX;
  const std::string TAG_MAX_USED_ITERATIONS;
  const std::string TAG_TIMESTEPS_REUSED;
  const std::string TAG_DATA;
  const std::string TAG_FILTER;
  const std::string TAG_ESTIMATEJACOBIAN;
  const std::string TAG_PRECONDITIONER;
  const std::string TAG_IMVJRESTART;

  const std::string ATTR_NAME;
  const std::string ATTR_MESH;
  const std::string ATTR_SCALING;
  const std::string ATTR_VALUE;
  const std::string ATTR_ENFORCE;
  const std::string ATTR_SINGULARITYLIMIT;
  const std::string ATTR_TYPE;
  const std::string ATTR_BUILDJACOBIAN;
  const std::string ATTR_IMVJCHUNKSIZE;
  const std::string ATTR_RSLS_REUSEDTSTEPS;
  const std::string ATTR_RSSVD_TRUNCATIONEPS;
  const std::string ATTR_PRECOND_NONCONST_TIMESTEPS;

  const std::string VALUE_CONSTANT;
  const std::string VALUE_AITKEN;
  const std::string VALUE_HIERARCHICAL_AITKEN;
  const std::string VALUE_IQNILS;
  const std::string VALUE_MVQN;
  const std::string VALUE_ManifoldMapping;
  const std::string VALUE_BROYDEN;
  const std::string VALUE_QR1FILTER;
  const std::string VALUE_QR1_ABSFILTER;
  const std::string VALUE_QR2FILTER;
  const std::string VALUE_CONSTANT_PRECONDITIONER;
  const std::string VALUE_VALUE_PRECONDITIONER;
  const std::string VALUE_RESIDUAL_PRECONDITIONER;
  const std::string VALUE_RESIDUAL_SUM_PRECONDITIONER;
  const std::string VALUE_LS_RESTART;
  const std::string VALUE_ZERO_RESTART;
  const std::string VALUE_SVD_RESTART;
  const std::string VALUE_SLIDE_RESTART;
  const std::string VALUE_NO_RESTART;

  //bool _isValid;

  const mesh::PtrMeshConfiguration _meshConfig;

  std::string _meshName;

  // post processing method
  impl::PtrPostProcessing _postProcessing;

  // recursive definition of post processings for multi level methods (i.e., manifold mapping)
  PtrPostProcessingConfiguration _coarseModelOptimizationConfig;

  std::vector<std::string> _neededMeshes;

  impl::PtrPreconditioner _preconditioner;

  struct ConfigurationData {
    std::vector<int>      dataIDs;
    std::map<int, double> scalings;
    std::string           type;
    double                relaxationFactor;
    bool                  forceInitialRelaxation;
    int                   maxIterationsUsed;
    int                   timestepsReused;
    int                   filter;
    int                   imvjRestartType;
    int                   imvjChunkSize;
    int                   imvjRSLS_reustedTimesteps;
    int                   precond_nbNonConstTSteps;
    double                singularityLimit;
    double                imvjRSSVD_truncationEps;
    bool                  estimateJacobian;
    bool                  alwaysBuildJacobian;
    std::string           preconditionerType;

    ConfigurationData()
        : dataIDs(),
          scalings(),
          type(""),
          relaxationFactor(0.0),
          forceInitialRelaxation(false),
          maxIterationsUsed(0),
          timestepsReused(0),
          filter(impl::PostProcessing::NOFILTER),
          imvjRestartType(0), // NO-RESTART
          imvjChunkSize(0),
          imvjRSLS_reustedTimesteps(0),
          precond_nbNonConstTSteps(-1),
          singularityLimit(0.0),
          imvjRSSVD_truncationEps(0.0),
          estimateJacobian(false),
          alwaysBuildJacobian(false),
          preconditionerType("")
    {
    }

  } _config;

  bool _isAddManifoldMappingTagAllowed;

  void addTypeSpecificSubtags(xml::XMLTag &tag);
};
}
} // namespace precice, cplscheme
