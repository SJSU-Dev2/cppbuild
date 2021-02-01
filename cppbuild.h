#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <numeric>
#include <string>
#include <typeinfo>
#include <vector>

#if !defined(BUILD_DISABLE_ANSI_CODES)
#define BUILD_COLOR_RESET "\e[0m"
// Color text
#define BUILD_BLACK "\e[0;30m"
#define BUILD_RED "\e[0;31m"
#define BUILD_GREEN "\e[0;32m"
#define BUILD_YELLOW "\e[0;33m"
#define BUILD_BLUE "\e[0;34m"
#define BUILD_PURPLE "\e[0;35m"
#define BUILD_CYAN "\e[0;36m"
#define BUILD_WHITE "\e[0;37m"
// Bold Color text
#define BUILD_BOLD_BLACK "\e[1;30m"
#define BUILD_BOLD_RED "\e[1;31m"
#define BUILD_BOLD_GREEN "\e[1;32m"
#define BUILD_BOLD_YELLOW "\e[1;33m"
#define BUILD_BOLD_BLUE "\e[1;34m"
#define BUILD_BOLD_PURPLE "\e[1;35m"
#define BUILD_BOLD_CYAN "\e[1;36m"
#define BUILD_BOLD_WHITE "\e[1;37m"
// Underline Color text
#define BUILD_UNDERLINE_BLACK "\e[4;30m"
#define BUILD_UNDERLINE_RED "\e[4;31m"
#define BUILD_UNDERLINE_GREEN "\e[4;32m"
#define BUILD_UNDERLINE_YELLOW "\e[4;33m"
#define BUILD_UNDERLINE_BLUE "\e[4;34m"
#define BUILD_UNDERLINE_PURPLE "\e[4;35m"
#define BUILD_UNDERLINE_CYAN "\e[4;36m"
#define BUILD_UNDERLINE_WHITE "\e[4;37m"
// High Intensity Color text
#define BUILD_HI_BLACK "\e[0;90m"
#define BUILD_HI_RED "\e[0;91m"
#define BUILD_HI_GREEN "\e[0;92m"
#define BUILD_HI_YELLOW "\e[0;93m"
#define BUILD_HI_BLUE "\e[0;94m"
#define BUILD_HI_PURPLE "\e[0;95m"
#define BUILD_HI_CYAN "\e[0;96m"
#define BUILD_HI_WHITE "\e[0;97m"
// High Intensity Color text
#define BUILD_HI_BOLD_BLACK "\e[1;90m"
#define BUILD_HI_BOLD_RED "\e[1;91m"
#define BUILD_HI_BOLD_GREEN "\e[1;92m"
#define BUILD_HI_BOLD_YELLOW "\e[1;93m"
#define BUILD_HI_BOLD_BLUE "\e[1;94m"
#define BUILD_HI_BOLD_PURPLE "\e[1;95m"
#define BUILD_HI_BOLD_CYAN "\e[1;96m"
#define BUILD_HI_BOLD_WHITE "\e[1;97m"
// Text Background color
#define BUILD_BACKGROUND_BLACK "\e[40m"
#define BUILD_BACKGROUND_RED "\e[41m"
#define BUILD_BACKGROUND_GREEN "\e[42m"
#define BUILD_BACKGROUND_YELLOW "\e[43m"
#define BUILD_BACKGROUND_BLUE "\e[44m"
#define BUILD_BACKGROUND_PURPLE "\e[45m"
#define BUILD_BACKGROUND_CYAN "\e[46m"
#define BUILD_BACKGROUND_WHITE "\e[47m"
// Text Background color
#define BUILD_HI_BACKGROUND_BLACK "\e[0;100m"
#define BUILD_HI_BACKGROUND_RED "\e[0;101m"
#define BUILD_HI_BACKGROUND_GREEN "\e[0;102m"
#define BUILD_HI_BACKGROUND_YELLOW "\e[0;103m"
#define BUILD_HI_BACKGROUND_BLUE "\e[0;104m"
#define BUILD_HI_BACKGROUND_PURPLE "\e[0;105m"
#define BUILD_HI_BACKGROUND_CYAN "\e[0;106m"
#define BUILD_HI_BACKGROUND_WHITE "\e[0;107m"
#else
#define BUILD_COLOR_RESET ""
// Color text
#define BUILD_BLACK ""
#define BUILD_RED ""
#define BUILD_GREEN ""
#define BUILD_YELLOW ""
#define BUILD_BLUE ""
#define BUILD_PURPLE ""
#define BUILD_CYAN ""
#define BUILD_WHITE ""
// Bold Color text
#define BUILD_BOLD_BLACK ""
#define BUILD_BOLD_RED ""
#define BUILD_BOLD_GREEN ""
#define BUILD_BOLD_YELLOW ""
#define BUILD_BOLD_BLUE ""
#define BUILD_BOLD_PURPLE ""
#define BUILD_BOLD_CYAN ""
#define BUILD_BOLD_WHITE ""
// Underline Color text
#define BUILD_UNDERLINE_BLACK ""
#define BUILD_UNDERLINE_RED ""
#define BUILD_UNDERLINE_GREEN ""
#define BUILD_UNDERLINE_YELLOW ""
#define BUILD_UNDERLINE_BLUE ""
#define BUILD_UNDERLINE_PURPLE ""
#define BUILD_UNDERLINE_CYAN ""
#define BUILD_UNDERLINE_WHITE ""
// High Intensity Color text
#define BUILD_HI_BLACK ""
#define BUILD_HI_RED ""
#define BUILD_HI_GREEN ""
#define BUILD_HI_YELLOW ""
#define BUILD_HI_BLUE ""
#define BUILD_HI_PURPLE ""
#define BUILD_HI_CYAN ""
#define BUILD_HI_WHITE ""
// High Intensity Color text
#define BUILD_HI_BOLD_BLACK ""
#define BUILD_HI_BOLD_RED ""
#define BUILD_HI_BOLD_GREEN ""
#define BUILD_HI_BOLD_YELLOW ""
#define BUILD_HI_BOLD_BLUE ""
#define BUILD_HI_BOLD_PURPLE ""
#define BUILD_HI_BOLD_CYAN ""
#define BUILD_HI_BOLD_WHITE ""
// Text Background color
#define BUILD_BACKGROUND_BLACK ""
#define BUILD_BACKGROUND_RED ""
#define BUILD_BACKGROUND_GREEN ""
#define BUILD_BACKGROUND_YELLOW ""
#define BUILD_BACKGROUND_BLUE ""
#define BUILD_BACKGROUND_PURPLE ""
#define BUILD_BACKGROUND_CYAN ""
#define BUILD_BACKGROUND_WHITE ""
// Text Background color
#define BUILD_HI_BACKGROUND_BLACK ""
#define BUILD_HI_BACKGROUND_RED ""
#define BUILD_HI_BACKGROUND_GREEN ""
#define BUILD_HI_BACKGROUND_YELLOW ""
#define BUILD_HI_BACKGROUND_BLUE ""
#define BUILD_HI_BACKGROUND_PURPLE ""
#define BUILD_HI_BACKGROUND_CYAN ""
#define BUILD_HI_BACKGROUND_WHITE ""

#endif  // !defined(BUILD_DISABLE_ANSI_CODES)

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

    auto space_out_strings = [](const std::string & ss, const std::string & s) {
      return ss.empty() ? s : ss + " " + s;
    };

    // Combine flags_ into build command
    build_command += std::accumulate(flags_.Get().begin(),
                                     flags_.Get().begin(),
                                     std::string{},
                                     space_out_strings);

    // Combine includes_ into build command
    build_command += std::accumulate(includes_.Get().begin(),
                                     includes_.Get().begin(),
                                     std::string{},
                                     space_out_strings);

    build_command += " -o " + object_path.string();
    build_command += " -c " + source_.string();

    printf("[Build] Object Command: %s\n", build_command.c_str());

    // Create directory in build directory
    std::filesystem::create_directories(object_path.parent_path());

    // Execute object build command
    system(build_command.c_str());
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
    printf("[Build] Build Program: %s\n", library_path_.c_str());
    std::string build_script = compiler + "-std=c++20 build.cpp -o build.exe";
    system(build_script.c_str());

    // Build: library
    printf("[Build] Static Library: %s\n", library_path_.c_str());
    system("./build.exe --static-library");

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
      // Create the build directory to hold all of this build artifacts
      std::filesystem::create_directories("./build");

      std::string static_library_list = "";
      for (auto & library : libraries_)
      {
        static_library_list += library.GetStaticLibraryPath().string() + " ";
        library.Build(compiler_);
      }

      std::string objects_list = "";
      for (auto & object : objects_)
      {
        objects_list += object.GetObjectPath().string() + " ";
        object.Compile(compiler_);
      }

      std::string link_command =
          linker_ + " -o " + name_ + " " + objects_list + static_library_list;

      printf("[Build] Link Command: %s\n", link_command.c_str());
      system(link_command.c_str());
    }
    catch (...)
    {
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

      printf("Archive Shell Command: %s\n", archive_command.c_str());
      printf("ranlib Shell Command: %s\n", ranlib_command.c_str());
      system(archive_command.c_str());
      system(ranlib_command.c_str());
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
