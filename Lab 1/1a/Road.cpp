// Lab 1a, Class Programming And Testing
// Programmer: Aldo Sanjoto
// Editor(s) used: Code::Blocks
// Compiler(s) used: Code::Blocks

#include "Road.h"

float Road::asphalt(float thickness) const
{
  float volume;

  volume = width * (length*5280) * (thickness/12);

  return volume;
}
