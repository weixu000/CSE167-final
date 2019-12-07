# https://glad.dav1d.de/
# OpenGL Core Profile 3.3
add_library(glad STATIC src/glad.c)
target_include_directories(glad PUBLIC include)