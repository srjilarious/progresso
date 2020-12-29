cmake_minimum_required(VERSION 3.10)

set (CMAKE_CXX_STANDARD 17)

# Simple ascii progress bar examples.
add_executable(
    ascii_bars
    ascii_bars.cpp
)

target_link_libraries(
    ascii_bars
    progresso
  )

# Unicode progress bar examples.
add_executable(
    unicode_bars
    unicode_bars.cpp
)

target_link_libraries(
    unicode_bars
    progresso
  )
