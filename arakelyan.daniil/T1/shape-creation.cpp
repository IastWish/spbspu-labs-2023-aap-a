#include <cstdlib>
#include <cstring>
#include "shape-creation.hpp"
#include "base-types.hpp"
#include "shape.hpp"
#include "parallelogram.hpp"
#include "diamond.hpp"
#include "rectangle.hpp"

void arakelyan::dataExtractionParAndDiam(const char * string, point_t & p1, point_t & p2, point_t & p3)
{
  double coordStorage[6] = {};

  for (int i = 0; i < 6; ++i)
  {
    while (* string == ' ' || * string == '\t')
    {
      ++string;
    }

    char * endPtr;
    coordStorage[i] = std::strtod(string, & endPtr);

    string = endPtr;
  }

  p1 = {coordStorage[0], coordStorage[1]};
  p2 = {coordStorage[2], coordStorage[3]};
  p3 = {coordStorage[4], coordStorage[5]};
}

void arakelyan::dataExtractionRect(const char * string, point_t & p1, point_t & p2)
{
  double coordStorage[4] = {};

  for (int i = 0; i < 4; ++i)
  {
    while (* string == ' ' || * string == '\t')
    {
      ++string;
    }

    char * endPtr;
    coordStorage[i] = std::strtod(string, & endPtr);


    string = endPtr;
  }

  p1 = {coordStorage[0], coordStorage[1]};
  p2 = {coordStorage[2], coordStorage[3]};
}


arakelyan::Shape * arakelyan::createPar(const char * string)
{
  point_t p1 = {0.0, 0.0};
  point_t p2 = {0.0, 0.0};
  point_t p3 = {0.0, 0.0};

  dataExtractionParAndDiam(string, p1, p2, p3);

  return new arakelyan::Parallelogram(p1, p2, p3);
}

arakelyan::Shape * arakelyan::createDiam(const char * string)
{
  point_t p1 = {0.0, 0.0};
  point_t p2 = {0.0, 0.0};
  point_t p3 = {0.0, 0.0};

  dataExtractionParAndDiam(string, p1, p2, p3);
  return new arakelyan::Diamond(p1, p2, p3);
}

arakelyan::Shape * arakelyan::createRect(const char * string)
{
  point_t p1 = {0.0, 0.0};
  point_t p2 = {0.0, 0.0};

  dataExtractionRect(string, p1, p2);
  return new arakelyan::Rectangle(p1, p2);
}

arakelyan::Shape * arakelyan::defineAndCreateShape(const char * string)
{
  const char * targetWordRectangle = "RECTANGLE";
  const char * targetWordParallelogram = "PARALLELOGRAM";
  const char * targetWordDiamond = "DIAMOND";
  const char * targetWordScale = "SCALE";

  const char * foundPar = std::strstr(string, targetWordParallelogram);
  const char * foundRect = std::strstr(string, targetWordRectangle);
  const char * foundDia = std::strstr(string, targetWordDiamond);
  const char * foundScale = std::strstr(string, targetWordScale);

  if (foundPar != nullptr)
  {
     return createPar(string);
  }
  if (foundRect != nullptr)
  {
     return createRect(string);
  }
  if (foundDia != nullptr)
  {
    return createDiam(string);
  }
  else
  {
    return nullptr;
  }
}
