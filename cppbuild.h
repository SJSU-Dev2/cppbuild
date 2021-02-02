#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <numeric>
#include <string>
#include <typeinfo>
#include <vector>

#if !defined(BUILD_DISABLE_ANSI_CODES)
#define COLOR_RESET "\e[0m"
// Color text
#define BLACK "\e[0;30m"
#define RED "\e[0;31m"
#define GREEN "\e[0;32m"
#define YELLOW "\e[0;33m"
#define BLUE "\e[0;34m"
#define PURPLE "\e[0;35m"
#define CYAN "\e[0;36m"
#define WHITE "\e[0;37m"
// Bold Color text
#define BOLD_BLACK "\e[1;30m"
#define BOLD_RED "\e[1;31m"
#define BOLD_GREEN "\e[1;32m"
#define BOLD_YELLOW "\e[1;33m"
#define BOLD_BLUE "\e[1;34m"
#define BOLD_PURPLE "\e[1;35m"
#define BOLD_CYAN "\e[1;36m"
#define BOLD_WHITE "\e[1;37m"
// Underline Color text
#define UNDERLINE_BLACK "\e[4;30m"
#define UNDERLINE_RED "\e[4;31m"
#define UNDERLINE_GREEN "\e[4;32m"
#define UNDERLINE_YELLOW "\e[4;33m"
#define UNDERLINE_BLUE "\e[4;34m"
#define UNDERLINE_PURPLE "\e[4;35m"
#define UNDERLINE_CYAN "\e[4;36m"
#define UNDERLINE_WHITE "\e[4;37m"
// High Intensity Color text
#define HI_BLACK "\e[0;90m"
#define HI_RED "\e[0;91m"
#define HI_GREEN "\e[0;92m"
#define HI_YELLOW "\e[0;93m"
#define HI_BLUE "\e[0;94m"
#define HI_PURPLE "\e[0;95m"
#define HI_CYAN "\e[0;96m"
#define HI_WHITE "\e[0;97m"
// High Intensity Color text
#define HI_BOLD_BLACK "\e[1;90m"
#define HI_BOLD_RED "\e[1;91m"
#define HI_BOLD_GREEN "\e[1;92m"
#define HI_BOLD_YELLOW "\e[1;93m"
#define HI_BOLD_BLUE "\e[1;94m"
#define HI_BOLD_PURPLE "\e[1;95m"
#define HI_BOLD_CYAN "\e[1;96m"
#define HI_BOLD_WHITE "\e[1;97m"
// Text Background color
#define BACKGROUND_BLACK "\e[40m"
#define BACKGROUND_RED "\e[41m"
#define BACKGROUND_GREEN "\e[42m"
#define BACKGROUND_YELLOW "\e[43m"
#define BACKGROUND_BLUE "\e[44m"
#define BACKGROUND_PURPLE "\e[45m"
#define BACKGROUND_CYAN "\e[46m"
#define BACKGROUND_WHITE "\e[47m"
// Text Background color
#define HI_BACKGROUND_BLACK "\e[0;100m"
#define HI_BACKGROUND_RED "\e[0;101m"
#define HI_BACKGROUND_GREEN "\e[0;102m"
#define HI_BACKGROUND_YELLOW "\e[0;103m"
#define HI_BACKGROUND_BLUE "\e[0;104m"
#define HI_BACKGROUND_PURPLE "\e[0;105m"
#define HI_BACKGROUND_CYAN "\e[0;106m"
#define HI_BACKGROUND_WHITE "\e[0;107m"
#else
#define COLOR_RESET ""
// Color text
#define BLACK ""
#define RED ""
#define GREEN ""
#define YELLOW ""
#define BLUE ""
#define PURPLE ""
#define CYAN ""
#define WHITE ""
// Bold Color text
#define BOLD_BLACK ""
#define BOLD_RED ""
#define BOLD_GREEN ""
#define BOLD_YELLOW ""
#define BOLD_BLUE ""
#define BOLD_PURPLE ""
#define BOLD_CYAN ""
#define BOLD_WHITE ""
// Underline Color text
#define UNDERLINE_BLACK ""
#define UNDERLINE_RED ""
#define UNDERLINE_GREEN ""
#define UNDERLINE_YELLOW ""
#define UNDERLINE_BLUE ""
#define UNDERLINE_PURPLE ""
#define UNDERLINE_CYAN ""
#define UNDERLINE_WHITE ""
// High Intensity Color text
#define HI_BLACK ""
#define HI_RED ""
#define HI_GREEN ""
#define HI_YELLOW ""
#define HI_BLUE ""
#define HI_PURPLE ""
#define HI_CYAN ""
#define HI_WHITE ""
// High Intensity Color text
#define HI_BOLD_BLACK ""
#define HI_BOLD_RED ""
#define HI_BOLD_GREEN ""
#define HI_BOLD_YELLOW ""
#define HI_BOLD_BLUE ""
#define HI_BOLD_PURPLE ""
#define HI_BOLD_CYAN ""
#define HI_BOLD_WHITE ""
// Text Background color
#define BACKGROUND_BLACK ""
#define BACKGROUND_RED ""
#define BACKGROUND_GREEN ""
#define BACKGROUND_YELLOW ""
#define BACKGROUND_BLUE ""
#define BACKGROUND_PURPLE ""
#define BACKGROUND_CYAN ""
#define BACKGROUND_WHITE ""
// Text Background color
#define HI_BACKGROUND_BLACK ""
#define HI_BACKGROUND_RED ""
#define HI_BACKGROUND_GREEN ""
#define HI_BACKGROUND_YELLOW ""
#define HI_BACKGROUND_BLUE ""
#define HI_BACKGROUND_PURPLE ""
#define HI_BACKGROUND_CYAN ""
#define HI_BACKGROUND_WHITE ""

#endif  // !defined(BUILD_DISABLE_ANSI_CODES)

void Print(const std::string & message)
{
  printf("%s\n", message.c_str());
}

void Print(const std::string & title, const std::string & message)
{
  printf("[%s] %s\n", title.c_str(), message.c_str());
}

void Print(const char * color,
           const std::string & title,
           const std::string & message)
{
  printf("%s[%s]" COLOR_RESET " %s\n", color, title.c_str(), message.c_str());
}

void Execute(const std::string & command)
{
  if constexpr (0)
  {
    Print(BOLD_PURPLE, "EXECUTE", command);
  }

  int error_occurred = system(command.c_str());

  if (error_occurred)
  {
    throw std::runtime_error("Command failed: " + command);
  }
}

class FlagsCommon
{
 public:
  const std::string & Get()
  {
    return flags_;
  }

 protected:
  std::string flags_;
};

class Flags : public FlagsCommon
{
 public:
  void Add(const std::string & flag)
  {
    flags_ += flag + " ";
  }
};

class Includes : public FlagsCommon
{
 public:
  void Add(const std::string & include)
  {
    flags_ += "-I " + include + " ";
  }
};

class Object
{
 public:
  Object(const std::filesystem::path & source) : source_(source) {}
  void AddIncludeDirectory(const std::string & include)
  {
    includes_.Add(include);
  }

  void SetIncludes(const Includes & includes)
  {
    includes_ = includes;
  }

  void SetFlags(const Flags & flags)
  {
    flags_ = flags;
  }

  void SetSource(const std::filesystem::path & source)
  {
    source_ = source;
  }

  void Compile(std::string & compiler)
  {
    auto object_path = GetObjectPath();

    std::string build_command = compiler + " -std=c++20 ";

    // Combine flags_ into build command
    build_command += flags_.Get() + " " + includes_.Get();
    build_command += " -o " + object_path.string();
    build_command += " -c " + source_.string();

    Print(YELLOW, "COMPILE", source_);

    // Create directory in build directory
    std::filesystem::create_directories(object_path.parent_path());

    // Execute object build command
    Execute(build_command);
  }

  std::filesystem::path GetObjectPath()
  {
    return "./build/" + source_.string() + ".obj";
  }

  std::filesystem::path source_;
  Includes includes_;
  Flags flags_;
};

class Library
{
 public:
  Library(std::filesystem::path library_path) noexcept
      : library_path_(library_path),
        build_source_path_(library_path_.string() + "/build.cpp"),
        build_executable_path_(library_path_.string() + "/build.exe"),
        static_library_path_(library_path_.string() + "build/library.a")
  {
  }

  const std::filesystem::path & GetStaticLibraryPath() const
  {
    return static_library_path_;
  }

  void Build(const std::string & compiler)
  {
    // Save the current location
    auto current_location = std::filesystem::current_path();

    // Change current working directory to the library directory
    std::filesystem::current_path(library_path_);

    // Build: build program
    // Print(CYAN, "BUILD", library_path_);
    std::string build_script = compiler + " -std=c++20 build.cpp -o build.exe";
    Execute(build_script);

    // Build: library
    Execute("./build.exe --static-library");

    // Returned to previous location
    std::filesystem::current_path(current_location);
  }

 private:
  std::filesystem::path library_path_;
  std::filesystem::path build_source_path_;
  std::filesystem::path build_executable_path_;
  std::filesystem::path static_library_path_;
};

class CommonFinalProduct
{
 public:
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

 protected:
  std::string name_     = "app.exe";
  std::string compiler_ = "g++";
  std::string linker_   = "g++";
  std::vector<Object> objects_;
  std::vector<Library> libraries_;
};

class Project : public CommonFinalProduct
{
 public:
  Project() {}

  int Build()
  {
    try
    {
      Print(CYAN, "PROJECT", std::filesystem::current_path());

      // Create the build directory to hold all of this build artifacts
      std::filesystem::create_directories("./build");

      Print("\nBuilding Libraries...\n");
      std::string static_library_list = "";
      for (auto & library : libraries_)
      {
        static_library_list += library.GetStaticLibraryPath().string() + " ";
        library.Build(compiler_);
      }

      Print("\nBuilding Project Source Files...\n");
      std::string objects_list = "";
      for (auto & object : objects_)
      {
        objects_list += object.GetObjectPath().string() + " ";
        object.Compile(compiler_);
      }

      Print("\nBuilding Final Executable...\n");
      std::string link_command =
          linker_ + " -o " + name_ + " " + objects_list + static_library_list;

      Print(GREEN, " FINAL ", name_);
      Execute(link_command);
    }
    catch (std::runtime_error & error)
    {
      Print(BOLD_RED, "EXCEPTION", error.what());
      return -1;
    }
    return 0;
  }
};

class StaticLibrary : public CommonFinalProduct
{
 public:
  StaticLibrary() {}

  int Build()
  {
    try
    {
      Print(CYAN, "LIBRARY", std::filesystem::current_path());

      // Create the build directory to hold all of this build artifacts
      std::filesystem::create_directories("./build");

      std::string objects_list = "";
      for (auto & object : objects_)
      {
        objects_list += object.GetObjectPath().string() + " ";
        object.Compile(compiler_);
      }

      std::string archive_command =
          archive_ + " rcs ./build/library.a " + objects_list;

      std::string ranlib_command = ranlib_ + " ./build/library.a";

      Print(GREEN, "ARCHIVE", std::filesystem::current_path());

      Execute(archive_command);
      Execute(ranlib_command);
    }
    catch (...)
    {
      return -1;
    }
    return 0;
  }

 private:
  std::string archive_ = "ar";
  std::string ranlib_  = "ranlib";
};

// -----------------------------------------------------------------------------
// Basic usage (in general)
// -----------------------------------------------------------------------------

// g++ build.cpp -o build_project.exe
// ./build_project.exe
// ./build_project.exe --produce-static-library
// ./build_project.exe --produce-objects
// ./build_project.exe --build-path="./my_build"

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
