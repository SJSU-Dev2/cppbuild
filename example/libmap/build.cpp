#include "../../cppbuild.h"

int main(int argc, const char * argv[])
{
  RebuildSelf();

  Object map("map.cpp");
  map.AddIncludeDirectory("./include");

  StaticLibrary library;
  library.AddObject(map);

  return library.Build();
}