# Caching the library name to be used in the parent scope.
set(PE_PATHLS_GENERATOR "sam_pe_pathls_generator" CACHE STRING "SAM PE pathls generator library name.")

file(GLOB PE_PATHLS_GENERATOR_HPP_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/pepathlscollector.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/pepathlsgenerator.hpp
)

file(GLOB PE_PATHLS_GENERATOR_CPP_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/pepathlscollector.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/pepathlsgenerator.cpp
)

# Safety check: Ensure that all the files exist.
foreach(file ${PE_PATHLS_GENERATOR_CPP_FILES} ${PE_PATHLS_GENERATOR_HPP_FILES})
    if(NOT EXISTS "${file}")
        message(FATAL_ERROR "File '${file}' does not exist!")
    endif()
endforeach()

add_library(${PE_PATHLS_GENERATOR} SHARED  
    ${PE_PATHLS_GENERATOR_CPP_FILES} 
)

set_target_properties(${PE_PATHLS_GENERATOR} PROPERTIES VERSION ${SAM_PROJECT_VERSION})

target_include_directories(${PE_PATHLS_GENERATOR} PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/" 
)

# Install the library.
# This is for CPack to be able to package the library.
install(TARGETS ${PE_PATHLS_GENERATOR} RUNTIME DESTINATION .)
