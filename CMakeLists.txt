cmake_minimum_required(VERSION 3.5)

set(_PROJET_NAME gitManage)
set(_PROJET_VERSION v1.0.1)

project(${_PROJET_NAME} VERSION 0.1 LANGUAGES CXX)

set(_PROJET_NAME_TARGET "")
string(CONCAT _PROJET_NAME_TARGET ${_PROJET_NAME} "_" ${_PROJET_VERSION})
message(${_PROJET_NAME_TARGET})

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    message("compile on windows")    
endif()

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core QUIET)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
    Core
    Gui
    Widgets
)

file(GLOB_RECURSE global_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/*.qrc
)
add_executable(${_PROJET_NAME}
    ${global_FILES}
)

target_link_libraries(${_PROJET_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
)

# ---- connect cMakeLists variable to Soft
add_compile_definitions(  cMake_softwarePath="${CMAKE_CURRENT_SOURCE_DIR}" )
add_compile_definitions(  cMake_binaryPath="${CMAKE_BINARY_DIR}" )
add_compile_definitions(  cMake_qtLibPath="${CMAKE_PREFIX_PATH}" )
add_compile_definitions(  cMake_qtVersion="${QT_VERSION}" )
add_compile_definitions(  cMake_projectName="${_PROJET_NAME}" )
add_compile_definitions(  cMake_projectVersion="${_PROJET_VERSION}" )
# ----

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set_target_properties( ${_PROJET_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
    set_target_properties( ${_PROJET_NAME} PROPERTIES WIN64_EXECUTABLE TRUE)

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack,1000000")
    message(${CMAKE_CXX_COMPILER_ID})
    message(${CMAKE_EXE_LINKER_FLAGS})
endif()

install(TARGETS ${_PROJET_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
