#pragma once

#include "com/SharedPointer.hpp"
#include "logging/Logger.hpp"
#include "mesh/Mesh.hpp"

namespace precice
{
namespace com
{

/// Copies a Mesh object from a sender to a receiver.
class CommunicateMesh
{
public:
  /// Constructor, takes communication to be used in transfer.
  explicit CommunicateMesh(
      com::PtrCommunication communication);

  /// Sends a constructed mesh to the receiver with given rank.
  void sendMesh(
      const mesh::Mesh &mesh,
      int               rankReceiver);

  /// Copies a mesh from the sender with given rank.
  void receiveMesh(
      mesh::Mesh &mesh,
      int         rankSender);

  void broadcastSendMesh(
      const mesh::Mesh &mesh);

  void broadcastReceiveMesh(
      mesh::Mesh &mesh);

  void sendBoundingBox(
      const mesh::Mesh::BoundingBox &bb,
      int                            rankReceiver);

  void receiveBoundingBox(
      mesh::Mesh::BoundingBox &bb,
      int                      rankSender);

private:
  logging::Logger _log{"com::CommunicateMesh"};
  
  /// Communication means used for the transfer of the geometry.
  com::PtrCommunication _communication;
};
} // namespace com
} // namespace precice
