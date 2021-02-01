#include "../cppbuild.h"

int main(int argc, const char * argv[])
{
  Library libaverage("./libaverage/");
  Library libmap("./libmap/");

  Object main("./main.cpp");
  main.AddIncludeDirectory("./libmap/include");
  main.AddIncludeDirectory("./libaverage/include");

  // Object map("./libmap/map.cpp");
  // map.AddIncludeDirectory("./libmap/include");

  // Object average("./libaverage/average.cpp");
  // average.AddIncludeDirectory("./libaverage/include");

  Project project;
  project.SetExecutableName("example.exe");
  project.AddLibrary(libaverage);
  project.AddLibrary(libmap);
  project.AddObject(main);
  // project.AddObject(map);
  // project.AddObject(average);

  return project.Build();
}