#include "../../cppbuild.h"

int main(int argc, const char * argv[])
{
  RebuildSelf();

  Object average("average.cpp");
  average.AddIncludeDirectory("./include");

  StaticLibrary library;
  library.AddObject(average);

  return library.Build();
}