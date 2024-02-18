#include <iostream>
#include <stdexcept>
#include <cstring>
#include <inputLine.hpp>
#include "base-types.hpp"
#include "inputAndOutputOperations.hpp"
#include "scaleOperations.hpp"
#include "shape-creation.hpp"
#include "shape.hpp"
#include "rectangle.hpp"
#include "diamond.hpp"
#include "parallelogram.hpp"

int main()
{
  using namespace arakelyan;
  size_t maxShapesCount = 1000;
  size_t currentShapesCount = 0;
  Shape ** myShapes = new Shape * [maxShapesCount]{nullptr};

  bool errorsFlagShapes = false;
  bool errorsFlagScale = false;

  point_t scalePoint = {0.0, 0.0};
  double scaleK = 0;
  const char * targetWordScale = "SCALE";

  char * string = nullptr;

  bool readingFromInput = true;

  while (readingFromInput)
  {
    try
    {
      string = inputString(std::cin);
    }
    catch (const std::exception &e)
    {
      for (size_t i = 0; i < currentShapesCount; i++)
      {
        delete myShapes[i];
      }
      delete [] myShapes;
      std::cerr << "Error: " << e.what() << "\n";
      return 1;
    }

    const char * foundScale = std::strstr(string, targetWordScale);
    if (foundScale != nullptr)
    {
      inputScaleParam(string, scalePoint, scaleK);

      try
      {
        scaleFunction(myShapes, currentShapesCount, scalePoint, scaleK);
      }
      catch (const std::logic_error &e)
      {
        errorsFlagScale = true;
      }

      readingFromInput = false;
    }
    else
    {
      try
      {
        myShapes[currentShapesCount] = defineAndCreateShape(string);
      }
      catch (const std::exception &e)
      {
        errorsFlagShapes = true;
      }

      if (myShapes[currentShapesCount] != nullptr)
      {
        currentShapesCount++;
      }
    }

    delete [] string;
  }

  if (errorsFlagShapes)
  {
    std::cerr << "Something went wrong with shapes creation!\n";
  }
  if (errorsFlagScale)
  {
    std::cerr << "Something went wrong with scale process!\n";
    for (size_t i = 0; i < currentShapesCount; i++)
    {
      delete myShapes[i];
    }
    delete [] myShapes;
    return 2;
  }

  if (currentShapesCount == 0)
  {
    std::cerr << "Nothing to scale!\n";
    for (size_t i = 0; i < currentShapesCount; i++)
    {
      delete myShapes[i];
    }
    delete [] myShapes;
    return 2;
  }

  for (size_t i = 0; i < currentShapesCount; i++)
  {
    delete myShapes[i];
  }
  delete [] myShapes;
  return 0;
}
