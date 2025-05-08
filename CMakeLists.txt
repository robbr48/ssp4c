cmake_minimum_required(VERSION 3.3)
project(ssp4c C)
set(CMAKE_C_STANDARD 99)

include(CMakeDependentOption)
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

option(SSP4C_BUILD_DOCUMENTATION "Build Doxygen documentation" OFF)
option(SSP4C_BUILD_TEST "Build test executable" OFF)
option(SSP4C_BUILD_SHARED "Build as shared library (DLL)" ON)
option(SSP4C_USE_SYSTEM_ZIP "Use system utilities for unzipping" ON)
option(SSP4C_USE_INCLUDED_ZLIB "Use the included zlib (statically linked) even if a system version is available" OFF)
#this option is only enabled when SSP4C_USE_SYSTEM_ZIP=OFF
cmake_dependent_option(SSP4C_USE_INCLUDED_ZLIB "Use the included zlib (statically linked) even if a system version is available" OFF "NOT SSP4C_USE_SYSTEM_ZIP" OFF)

if (NOT DEFINED SSP4C_EXTERNAL_MINIZIP)
    set(SSP4C_EXTERNAL_MINIZIP "" CACHE STRING "Defines an external target for minizip.")
endif()

# Set default debug postfix
if (NOT CMAKE_DEBUG_POSTFIX)
    set(CMAKE_DEBUG_POSTFIX )
endif()

if (${SSP4C_BUILD_DOCUMENTATION})
    add_subdirectory(doc)
endif()

if(NOT SSP4C_USE_EXTERNAL_MINIZIP)
    if (NOT SSP4C_USE_SYSTEM_ZIP)
        if(NOT SSP4C_USE_INCLUDED_ZLIB)
            find_package(ZLIB MODULE)
            message(STATUS "ZLIB_FOUND: ${ZLIB_FOUND}")
            message(STATUS "ZLIB_INCLUDE_DIRS: ${ZLIB_INCLUDE_DIRS}")
            message(STATUS "ZLIB_VERSION: ${ZLIB_VERSION} ${ZLIB_VERSION_STRING}")
            message(STATUS "ZLIB_LIBRARIES: ${ZLIB_LIBRARIES}")
        endif()
        # If zlib can not be found in the system, then build local version
        if (NOT ZLIB_FOUND)
            set(zlib_dir "3rdparty/zlib")
            message(STATUS "Building and using included ZLIB: ${zlib_dir}")
            # Must use position independent code if intend to include static zlib into shared (dll) ssp4c lib
            set(CMAKE_POSITION_INDEPENDENT_CODE ON)
            # Add bundled sources, (EXCLUDE_FROM_ALL prevents zlib from being installed with ssp4c)
            add_subdirectory(${zlib_dir} EXCLUDE_FROM_ALL)
            # We highjack the zlibstatic target from the original build system, but it does not have the include directory properties set, so lets add them here
            set_target_properties(zlibstatic
                    PROPERTIES
                    INTERFACE_INCLUDE_DIRECTORIES
                    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${zlib_dir}>;$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${zlib_dir}>")
            # Use alias to match name that find-module uses
            add_library(ZLIB::ZLIB ALIAS zlibstatic)
        endif()
    endif()
endif()

set(SRCFILES
    src/ssp4c.c
    src/ssp4c_utils.c
    include/ssp4c.h
    include/ssp4c_utils.h
    include/ssp4c_private.h
    include/ssp4c_public.h
    3rdparty/ezxml/ezxml.c
    3rdparty/ezxml/ezxml.h)
if (WIN32)
    SET(SRCFILES ${SRCFILES} 3rdparty/minizip/iowin32.c)
endif()
if (MSVC)
    SET(SRCFILES ${SRCFILES} 3rdparty/dirent/dirent.h)
endif()

if(NOT SSP4C_USE_EXTERNAL_MINIZIP)
    if (NOT SSP4C_USE_SYSTEM_ZIP)

        list(APPEND SRCFILES
                3rdparty/minizip/minizip.c
                3rdparty/minizip/miniunz.c
                3rdparty/minizip/ioapi.c
                3rdparty/minizip/mztools.c
                3rdparty/minizip/unzip.c
                3rdparty/minizip/zip.c
        )

        if (WIN32)
            list(APPEND SRCFILES 3rdparty/minizip/iowin32.c)
        endif()

    endif ()
endif()

if (SSP4C_BUILD_SHARED)
    add_library(ssp4c SHARED ${SRCFILES}
        include/ssp4c_common.h)
else()
    add_library(ssp4c STATIC ${SRCFILES})
endif()

target_compile_definitions(ssp4c PUBLIC HAVE_MEMMOVE=1 EZXML_NOMMAP USE_FILE32API)
if (SSP4C_BUILD_SHARED)
    # Only set DLLEXPORT when producing the library, when consumed dllimport will be assumed
    target_compile_definitions(ssp4c PRIVATE SSP4C_DLLEXPORT)
else()
    # When using as a static library (on windows) SSP4C_STATIC must be defined, otherwise dllimport will be assumed
    target_compile_definitions(ssp4c PUBLIC SSP4C_STATIC)
    # Must use position independent code if intend to include static ssp4c lib into shared (dll) consumer
    set_target_properties(ssp4c PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif()

target_include_directories(ssp4c
        PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/3rdparty>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
        PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

if(NOT SSP4C_USE_EXTERNAL_MINIZIP)
    target_include_directories(ssp4c PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/3rdparty>/minizip")
endif()

# Internal dependecy (PRIVATE) on zlib and ${CMAKE_DL_LIBS}) for libdl on Linux
target_link_libraries(ssp4c PRIVATE ${CMAKE_DL_LIBS})

if(SSP4C_USE_EXTERNAL_MINIZIP)
    message(STATUS "Using external MINIZIP: ${SSP4C_EXTERNAL_MINIZIP}")
    target_link_libraries(ssp4c PUBLIC ${SSP4C_EXTERNAL_MINIZIP})
    target_compile_definitions(ssp4c PRIVATE SSP4C_WITH_MINIZIP)
else()
    message(STATUS "NOT using external MINIZIP")
    if (NOT SSP4C_USE_SYSTEM_ZIP)
        # Internal dependency (PRIVATE) on zlib
        message(STATUS "NOT using system zip")
        target_link_libraries(ssp4c PRIVATE ZLIB::ZLIB)
        target_compile_definitions(ssp4c PRIVATE SSP4C_WITH_MINIZIP)
    endif()
endif()

if (SSP4C_BUILD_TEST)
    enable_testing()
    add_subdirectory(test)
    if (WIN32 AND SSP4C_BUILD_SHARED)
        add_custom_command(TARGET ssp4c POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:ssp4c> "${CMAKE_CURRENT_BINARY_DIR}/test")
    endif()
endif()


configure_package_config_file(cmake/config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/ssp4c-config.cmake"
        INSTALL_DESTINATION "${CMAKE_INSTALL_DATADIR}/ssp4c"
        NO_SET_AND_CHECK_MACRO)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/ssp4c-config.cmake"
        DESTINATION "${CMAKE_INSTALL_DATADIR}/ssp4c")

if(NOT SSP4C_USE_EXTERNAL_MINIZIP)
    install(TARGETS ssp4c EXPORT "ssp4c-targets")
endif()

install(DIRECTORY "include/" DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
install(DIRECTORY "3rdparty/ssp" DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

if(NOT SSP4C_USE_EXTERNAL_MINIZIP)
    # If building a static library, also include the local static zlib if it was built
    if (NOT SSP4C_USE_SYSTEM_ZIP AND NOT SSP4C_BUILD_SHARED AND TARGET zlibstatic)
        install(TARGETS zlibstatic EXPORT "ssp4c-targets")
    endif()

    install(EXPORT "ssp4c-targets"
            NAMESPACE "ssp4c::"
            DESTINATION "${CMAKE_INSTALL_DATADIR}/ssp4c")
endif()
