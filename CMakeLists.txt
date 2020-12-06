# Written by Nathan McCulloch

# Minimum CMake version required
cmake_minimum_required(VERSION 3.0)

# Set c++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(RenderEngine)

add_subdirectory(external/glfw-3.3.2)
add_subdirectory(external/GLAD)

include_directories(
    external/glfw-3.3.2/include
    external/GLAD/include
    external/
    ${CMAKE_SOURCE_DIR}/src/
)


add_executable(RenderEngine
    src/main.cpp
    src/Shader.cpp
    src/stb_image.cpp
    src/Camera.cpp
    src/Controls.cpp
    src/Texture.cpp
    src/Scene.cpp
    src/ObjLoader.cpp
    src/Object.cpp
    src/Cube.cpp
    src/ImGui/imgui.cpp
    src/ImGui/imgui_demo.cpp
    src/ImGui/imgui_draw.cpp
    src/ImGui/imgui_widgets.cpp
)

target_link_libraries(RenderEngine PRIVATE glad glfw ${GLFW_LIBRARIES})

SET(CMAKE_CXX_FLAGS " -lGL -lX11 -lpthread -ldl")