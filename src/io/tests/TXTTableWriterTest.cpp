#include "io/TXTTableWriter.hpp"
#include "testing/Testing.hpp"

BOOST_AUTO_TEST_SUITE(IOTests)

using namespace precice::io;

BOOST_AUTO_TEST_CASE(TXTTableWriterTest, * precice::testing::OnMaster())
{
  TXTTableWriter writer("io-TXTTableWriterTest.txt");
  writer.addData("Timestep", TXTTableWriter::INT);
  writer.addData("Flowrate", TXTTableWriter::DOUBLE);
  writer.addData("Force2D", TXTTableWriter::VECTOR2D);
  writer.addData("Force3D", TXTTableWriter::VECTOR3D);

  for (int t = 0; t < 10; t++) {
    writer.writeData("Timestep", t);
    writer.writeData("Flowrate", 0.0 + (double) t);
    writer.writeData("Force2D", Eigen::Vector2d(0.0 + 2.0 * (double) t,
                                                0.0 + 2.0 * (double) t));
    writer.writeData("Force3D", Eigen::Vector3d(0.0 + 2.0 * (double) t,
                                                0.0 + 2.0 * (double) t,
                                                0.0 + 2.0 * (double) t));
  }
  writer.close();
}

BOOST_AUTO_TEST_SUITE_END() // IOTests
