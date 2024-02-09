# CMakeList.txt : CMake project for Space, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(SP_STD_BUILD_EXAMPLES ON)

if(${SP_STD_BUILD_EXAMPLES} MATCHES ON)
    
    project (SP_STD CXX)
    
    # For Cpp_Properties
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

    # For Debug
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g") 
    
    function(include_dirs)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/${includes}" PARENT_SCOPE) 
    endfunction()

    set(includes "Include/")
    include_dirs()
    
    # Sets the output dirs
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE})

    # Add source to this project's executable.
    add_executable (Example Examples.cpp)

    target_link_libraries(Example stdc++)

endif()