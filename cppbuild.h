#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <string>
#include <typeinfo>
#include <vector>

class Flags
{
 public:
  void Add(std::string flag)
  {
    flags_.push_back(flag);
  }

  std::vector<std::string> & Get()
  {
    return flags_;
  }

  std::vector<std::string> flags_;
};

class Includes
{
 public:
  void Add(std::string include)
  {
    includes_.push_back(include);
  }

  std::vector<std::string> & Get()
  {
    return includes_;
  }

  std::vector<std::string> includes_;
};

class Object
{
 public:
  Object(std::filesystem::path source) : source_(source) {}
  void AddIncludeDirectory(std::string include)
  {
    includes_.Add(include);
  }
  void SetIncludes(Includes & includes)
  {
    includes_ = includes;
  }

  void AddFlagsDirectory(std::string flags)
  {
    flags_.Add(flags);
  }

  void SetFlags(Flags & flags)
  {
    flags_ = flags;
  }

  void SetSource(std::filesystem::path source)
  {
    source_ = source;
  }

  void Generate()
  {
    auto object_path = GetObjectPath();
    printf("Using '%s' to generating object: '%s'\n",
           compiler_.c_str(),
           object_path.c_str());

    std::string compiler_command = compiler_ + " -std=c++20 ";

    for (const auto & flags : flags_.Get())
    {
      printf("\t Flags: %s\n", flags.c_str());
      compiler_command += flags + " ";
    }

    for (const auto & includes : includes_.Get())
    {
      printf("\t Include: %s\n", includes.c_str());
      compiler_command += "-I" + includes + " ";
    }

    compiler_command +=
        "-c -o " + object_path.string() + " " + source_.string();

    printf("\t Shell Command: %s\n", compiler_command.c_str());
    std::filesystem::create_directories(object_path.parent_path());
    system(compiler_command.c_str());
  }

  std::filesystem::path GetObjectPath()
  {
    return "./build/" + source_.string() + ".obj";
  }

  std::string compiler_ = "g++";
  std::filesystem::path source_;
  Includes includes_;
  Flags flags_;
};

class Library
{
 public:
  Library(std::filesystem::path library_path) : library_path_(library_path) {}

  std::filesystem::path GetLibraryPath()
  {
    return "build/" + library_path_.string() + ".a";
  }

  void CompileBuildProgram()
  {

  }

  // void Generate()
  // {
  //   printf("Using '%s' to generating object: '%s.obj'\n", compiler_,
  //          source_.c_str());

  //   for (const auto &flags : flags_.Get())
  //   {
  //     printf("\t Flags: %s\n", flags.c_str());
  //   }

  //   for (const auto &includes : includes_.Get())
  //   {
  //     printf("\t Include: %s\n", includes.c_str());
  //   }
  // }

  std::filesystem::path library_path_;
};

class Project
{
 public:
  Project() {}

  void SetLinker(std::string linker)
  {
    linker_ = linker;
  }
  void SetExecutableName(std::string name)
  {
    name_ = name;
  }
  void AddLibrary(Library & library)
  {
    libraries_.push_back(library);
  }
  void AddObject(Object & object)
  {
    objects_.push_back(object);
  }

  int Generate()
  {
    try
    {
      std::filesystem::create_directories("./build");

      for (auto &library : libraries_)
      {
        library.CompileBuildProgram();
      }

      // for (auto &library : libraries_)
      // {
      //   library.Build();
      //   library_paths.push_back(library.GetLibraryPath());
      // }

      std::string objects_list_ = "";
      for (auto & object : objects_)
      {
        objects_list_ += object.GetObjectPath().string() + " ";
        object.Generate();
        // object_paths.push_back(object.GetObjectPath());
      }

      printf("Using '%s' to linking: '%s'\n", linker_.c_str(), name_.c_str());

      // for (auto & object_path : object_paths)
      // {
      //   printf("\t OBJ: '%s'\n", object_path.c_str());
      // }

      std::string link_command = linker_ + " -o " + name_ + " " + objects_list_;

      printf("\t Link Shell Command: %s\n", link_command.c_str());
      system(link_command.c_str());
    }
    catch (...)
    {
      return -1;
    }
    return 0;
  }

  std::string name_   = "app.exe";
  std::string linker_ = "g++";
  std::vector<Object> objects_;
  std::vector<Library> libraries_;
};

// -----------------------------------------------------------------------------
// Basic usage (in general)
// -----------------------------------------------------------------------------

// g++ build.cpp -o build_project.exe
// ./build_project.exe
// ./build_project.exe --produce-static-library
// ./build_project.exe --produce-objects
// ./build_project.exe --build-path="./build"

// -----------------------------------------------------------------------------
// SJSU-Dev2: lpc40xx/stm32f10x/stm32f4xx
// -----------------------------------------------------------------------------

// g++ build.cpp -o build_project.exe
// ./build_project.exe --platform=lpc40xx
// ./build_project.exe --platform=stm32f10x
// ./build_project.exe --platform=stm32f4xx

// -----------------------------------------------------------------------------
// SJSU-Dev2: JTAG
// -----------------------------------------------------------------------------

// g++ build.cpp -o build_project.exe
// ./build_project.exe --platform=lpc40xx --jtag=stlink
// ./build_project.exe --platform=stm32f10x --jtag=jlink
// ./build_project.exe --platform=stm32f4xx --jtag=stlink

// -----------------------------------------------------------------------------
// SJSU-Dev2: Presets
// -----------------------------------------------------------------------------

// g++ build.cpp -o build_project.exe
// ./build_project.exe --preset=arm.preset
// ./build_project.exe --preset=drive.preset
// ./build_project.exe --preset=PODS.preset
