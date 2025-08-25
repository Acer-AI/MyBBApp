cmake_minimum_required(VERSION 3.16)
project(BBApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Use Qt 6.9 (Widgets, Gui, Core, OpenGL Widgets if needed)
find_package(Qt6 6.9 COMPONENTS Core Gui Widgets OpenGLWidgets PrintSupport REQUIRED)

# Collect sources (recurses the src/ tree). Adjust globs if you want stricter control.
file(GLOB_RECURSE SRC_FILES
    CONFIGURE_DEPENDS
    src/*.cpp
    src/*.c
    src/*.cc
)

file(GLOB_RECURSE HEADER_FILES
    CONFIGURE_DEPENDS
    src/*.h
    src/*.hpp
)

# Include resources (expects resources/bb_app.qrc to exist as in original repo)
set(BBAPP_QRC resources/bb_app.qrc)
qt_add_resources(BBAPP_RCS ${BBAPP_QRC})

# Create executable
add_executable(BBApp
    ${SRC_FILES}
    ${HEADER_FILES}
    ${BBAPP_RCS}
)

# Include project headers and compatibility shims
target_include_directories(BBApp PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/compat
)

# Link Qt6
target_link_libraries(BBApp PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::OpenGLWidgets
    Qt6::PrintSupport
)

# If you need to link vendor libs such as bb_api / sa_api, add find_library() here and link them:
# find_library(BB_API_LIB bb_api PATHS "${CMAKE_CURRENT_SOURCE_DIR}/libs" NO_DEFAULT_PATH)
# if (BB_API_LIB)
#     target_link_libraries(BBApp PRIVATE ${BB_API_LIB})
# endif()

# On Windows, set GUI subsystem to avoid console window (optional)
if (WIN32)
    set_target_properties(BBApp PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

# Helpful compile-time defs (optional): enable Qt deprecated APIs if you rely on them.
# target_compile_definitions(BBApp PRIVATE QT_DISABLE_DEPRECATED_BEFORE=0x060000)

# Installation (optional)
install(TARGETS BBApp RUNTIME DESTINATION bin)
