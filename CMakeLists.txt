cmake_minimum_required(VERSION 3.10)
project(Beyrl)

add_subdirectory("libs/glad")

add_subdirectory("libs/glfw")
add_library(glfwInterface INTERFACE)
target_link_libraries(glfwInterface INTERFACE glfw)
target_include_directories(glfwInterface INTERFACE "libs/glfw/include")

add_subdirectory("libs/stb")

add_library(beyrl STATIC
    "src/graphics/context.cpp"
    "src/graphics/window.cpp"
    "src/graphics/shader.cpp"
    "src/graphics/model.cpp"
    "src/graphics/texture.cpp"
    "src/graphics/objparser.cpp"
)
target_include_directories(beyrl
PUBLIC
    "include/"
PRIVATE
    "src"
)
target_link_libraries(beyrl PRIVATE glfwInterface glad stb_image)
target_compile_features(beyrl PUBLIC cxx_std_20)