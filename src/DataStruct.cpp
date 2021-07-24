#include "DataStruct.hpp"

std::ostream& operator<< (std::ostream &s, const CommandsStruct &c)
{
    s << "VectorArray: ["
      << c.VectorArray[0] << ", "
      << c.VectorArray[1] << ", "
      << c.VectorArray[2] << ", "
      << c.VectorArray[3] << ", "
      << c.VectorArray[4] << ", "
      << c.VectorArray[5] << "]"
      << "\n"

      << "The Hand: ["
      << c.TheHand[0] << ", "
      << c.TheHand[1] << "]"
      << "\n"

      << "Camera: ["
      << c.Camera[0] << ", "
      << c.Camera[1] << "]"
      << "\n"

      << "MotorsLock: "
      << c.MotorsLock << "\n"

      << "Stabilization: "
      << c.Stabilization << std::endl;

    return s;
}