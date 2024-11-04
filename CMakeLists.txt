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

# Installation target
install(TARGETS SYNAPSIS DESTINATION bin)

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
message(STATUS "  cmake --install .    # Install SYNAPSIS to bin/")
message(STATUS "  cmake --build . --target clean # Clean up build files")