cmake_minimum_required(VERSION 3.21)
project(game LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generate compile_commands.json for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---------------------------- Project Files -------------------------------------
#file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR}/$<CONFIG>) # Copy assets to the output directory of the executable

# Set Target
add_executable(${PROJECT_NAME})

# Main sources files
file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.inl"
)

target_sources(${PROJECT_NAME} PRIVATE ${GAME_SOURCES})

# Include files
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Libarires
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# ------------------------------- Linking -------------------------------------------

# Windows
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE raylib winmm gdi32 opengl32)
endif()

# Linux:
if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE libraylib m pthread dl GL X11)
endif()

# macOS:
if(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreAudio"
        "-framework CoreVideo"
        "-framework AudioToolbox"
    )
endif()

# Copy compile_commands.json to root dir
add_custom_command(
    OUTPUT "${CMAKE_SOURCE_DIR}/compile_commands.json"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_BINARY_DIR}/compile_commands.json"
            "${CMAKE_SOURCE_DIR}/compile_commands.json"
    DEPENDS "${CMAKE_BINARY_DIR}/compile_commands.json"
)

add_custom_target(copy_compile_commands ALL
    DEPENDS "${CMAKE_SOURCE_DIR}/compile_commands.json"
)