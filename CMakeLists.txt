cmake_minimum_required(VERSION 3.10)

project(Game LANGUAGES CXX)

# Imposta lo standard C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Richiedi il supporto wide-character per ncursesw
set(CURSES_NEED_WIDE TRUE)

# Trova la libreria ncurses con supporto wide
find_package(Curses REQUIRED)

# ------------------------------------------------------------------------------
# Sorgenti del gioco
# ------------------------------------------------------------------------------

# Tutti i .cpp dentro src/ (ricorsivo)
file(GLOB_RECURSE SOURCES
  "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

# ------------------------------------------------------------------------------
# Libreria NcWrapper (i file dentro NcWrapper)
# ------------------------------------------------------------------------------

# Tutti i .cpp dentro NcWrapper/
file(GLOB NcWrapper_SOURCES
  "${CMAKE_SOURCE_DIR}/NcWrapper/*.cpp"
)

add_library(NcWrapper STATIC
  ${NcWrapper_SOURCES}
)

# Include visibili a chi usa NcWrapper
target_include_directories(NcWrapper
  PUBLIC
    ${CMAKE_SOURCE_DIR}/NcWrapper
    ${CURSES_INCLUDE_DIR}
)

# Se NcWrapper usa ncurses, linka qui in modo transitivo
target_link_libraries(NcWrapper
  PUBLIC
    ${CURSES_LIBRARIES}
)

# ------------------------------------------------------------------------------
# Eseguibile del gioco
# ------------------------------------------------------------------------------

add_executable(Game
  ${SOURCES}
)

# Include specifici del gioco
target_include_directories(Game
  PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# Linka la libreria NcWrapper (che a sua volta linka ncurses)
target_link_libraries(Game
  PRIVATE
    NcWrapper
)

# Flag di compilazione
target_compile_options(Game PRIVATE
  -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion 
  -Wcast-align -Wcast-qual -Wold-style-cast -Woverloaded-virtual 
  -Wnon-virtual-dtor -Weffc++ -Wundef -Wuninitialized -Werror
)
