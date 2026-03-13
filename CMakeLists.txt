cmake_minimum_required(VERSION 3.16)

project(Bomberman LANGUAGES CXX)

# ------------------------------------------------------------------------------
# Standard C++
# ------------------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ------------------------------------------------------------------------------
# ncurses (portabile Mac/Linux)
# ------------------------------------------------------------------------------

# Aggiunge il prefix path di Homebrew su macOS automaticamente
if(APPLE)
    list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew/opt/ncurses")
endif()

set(CURSES_NEED_WIDE TRUE)
find_package(Curses REQUIRED)

# ------------------------------------------------------------------------------
# Sorgenti
# ------------------------------------------------------------------------------

file(GLOB_RECURSE Bomberman_SOURCES
  CONFIGURE_DEPENDS
  src/*.cpp
)

file(GLOB NCWRAPPER_SOURCES
  CONFIGURE_DEPENDS
  NcWrapper/*.cpp
)

# ------------------------------------------------------------------------------
# Libreria NcWrapper
# ------------------------------------------------------------------------------

add_library(NcWrapper STATIC
  ${NCWRAPPER_SOURCES}
)

target_include_directories(NcWrapper
  PUBLIC
    ${CMAKE_SOURCE_DIR}/NcWrapper
    ${CURSES_INCLUDE_DIR}
)

target_link_libraries(NcWrapper
  PUBLIC
    ${CURSES_LIBRARIES}
)

target_compile_features(NcWrapper PUBLIC cxx_std_20)

# ------------------------------------------------------------------------------
# Eseguibile
# ------------------------------------------------------------------------------

add_executable(Bomberman
  ${Bomberman_SOURCES}
)

target_include_directories(Bomberman
  PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(Bomberman
  PRIVATE
    NcWrapper
)

# ------------------------------------------------------------------------------
# Warning portabili GCC / Clang
# ------------------------------------------------------------------------------

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(Bomberman PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wconversion
    -Wsign-conversion
    -Wcast-align
    -Wcast-qual
    -Wold-style-cast
    -Woverloaded-virtual
    -Wnon-virtual-dtor
    -Wundef
  )
endif()

# Warning extra per GCC
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(Bomberman PRIVATE
    -Wuseless-cast
    -Wlogical-op
  )
endif()