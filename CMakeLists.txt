cmake_minimum_required(VERSION 3.14)

project(SpacedRepetition)

# add all .cpp files in the src/ directory
file(GLOB SOURCES "src/*.cpp")

# add executables and link source files
add_executable(spaced_repetition_test ${SOURCES})

# add include directories
target_include_directories(spaced_repetition_test PUBLIC include)

# fetch gtest
include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Now simply link against gtest or gtest_main as needed. Eg
target_link_libraries(spaced_repetition_test gtest_main)
#target_link_libraries(spaced_repetition_test gtest)
#add_test(NAME example_test COMMAND example)