cmake_minimum_required(VERSION 3.20)

project(hello_wasm VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -s USE_SDL=2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -s USE_SDL=2")

# Ensure Emscripten toolchain is used
if(NOT EMSCRIPTEN)
  message(FATAL_ERROR "Configure with 'emcmake cmake -S . -B build' or set CMAKE_TOOLCHAIN_FILE to Emscripten's Emscripten.cmake")
endif()

# Options
option(GENERATE_HTML "Generate an HTML launcher instead of only .js/.wasm" ON)
option(OPTIMIZE_FOR_SIZE "Optimize for code size" OFF)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)



# Sources
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
add_executable(hello
  "${SRC_DIR}/hello.cpp"
)

# Warnings
target_compile_options(hello PRIVATE -Wall -Wextra -fno-exceptions -fno-rtti)

# Output name and directory
set_target_properties(hello PROPERTIES
  OUTPUT_NAME "hello"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/dist"
)

# Emscripten-specific settings
if(GENERATE_HTML)
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()

if(OPTIMIZE_FOR_SIZE)
  target_compile_options(hello PRIVATE -Os)
  target_link_options(hello PRIVATE -Os)
else()
  target_compile_options(hello PRIVATE -O2)
  target_link_options(hello PRIVATE -O2)
endif()

# Keep memory small and avoid leaks/long-running issues
target_link_options(hello PRIVATE
  "SHELL:-sALLOW_MEMORY_GROWTH=1"  # grow as needed, small initial footprint
  "SHELL:-sEXIT_RUNTIME=1"         # exit cleanly when main returns
  "SHELL:-sNO_FILESYSTEM=1"        # no FS to reduce size when not needed
  "SHELL:-sASSERTIONS=1"        
  -g0                               # strip debug info for minimal size
)

target_link_libraries(hello
    SDL2
)
