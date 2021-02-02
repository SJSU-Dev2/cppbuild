#include "../cppbuild.h"

int main(int argc, const char * argv[])
{
  RebuildSelf();

  Library libaverage("./libaverage/");
  Library libmap("./libmap/");

  Object main("./main.cpp");
  main.AddIncludeDirectory("./libmap/include");
  main.AddIncludeDirectory("./libaverage/include");

  Project project;
  project.AddLibrary(libaverage);
  project.AddLibrary(libmap);
  project.AddObject(main);

  return project.Build();
}