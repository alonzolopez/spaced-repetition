cmake_minimum_required(VERSION 3.14)

project(SpacedRepetition)

# add all .cpp files in the src/ directory
file(GLOB SOURCES "src/*.cpp")

# add executables and link source files
add_executable(spaced_repetition_test ${SOURCES})

# add include directories
target_include_directories(spaced_repetition_test PUBLIC include)

# FetchContent section
include(FetchContent)

# fetch gtest
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# fetch jsonlines
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

# Now simply link against gtest or gtest_main as needed. Eg
target_link_libraries(spaced_repetition_test gtest_main nlohmann_json::nlohmann_json)
# target_link_libraries(spaced_repetition_test PRIVATE )

