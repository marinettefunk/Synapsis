cmake_minimum_required(VERSION 3.10)

# Project name
project(SYNAPSIS VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Source files
set(SOURCES
    welcome.cpp
    profile.cpp
    main.cpp
    menu.cpp
    formatting.cpp
    files.cpp
    chat.cpp
)

# Header files
set(HEADERS
    welcome.h
    profile.h
    menu.h
    formatting.h
    files.h
    chat.h
)

# Create the executable
add_executable(SYNAPSIS ${SOURCES} ${HEADERS})

# Ensure that the executable goes to the correct directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug)

# Define a default install location based on architecture
if(WIN32)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)  # Check if building for 64-bit
        set(DEFAULT_INSTALL_DIR "$ENV{ProgramFiles}/SYNAPSIS")
    else()  # Building for 32-bit
        set(DEFAULT_INSTALL_DIR "$ENV{ProgramFiles(x86)}/SYNAPSIS")
    endif()
    set(CMAKE_INSTALL_PREFIX "${DEFAULT_INSTALL_DIR}" CACHE PATH "Install path" FORCE)
endif()

# Installation target
install(TARGETS SYNAPSIS DESTINATION bin)

# Automatically add the installation path to the user's PATH
if(WIN32)
    install(CODE "execute_process(COMMAND setx PATH \"%PATH%;${DEFAULT_INSTALL_DIR}/bin\")")
endif()

# Add custom command for cleaning
set_property(DIRECTORY PROPERTY ADDITIONAL_MAKE_CLEAN_FILES "${CMAKE_BINARY_DIR}/SYNAPSIS")

# Help command
if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
    message(STATUS "Build type: DEBUG")
else()
    message(STATUS "Build type: RELEASE")
endif()

message(STATUS "Commands:")
message(STATUS "  cmake --build .      # Build the executable")
message(STATUS "  cmake --install .    # Install SYNAPSIS to ${CMAKE_INSTALL_PREFIX}")
message(STATUS "  cmake --build . --target clean # Clean up build files")