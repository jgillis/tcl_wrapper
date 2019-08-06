
cmake_minimum_required(VERSION 3.7 FATAL_ERROR)
project (TCL_WRAPPER C CXX)

include_directories(${PROJECT_SOURCE_DIR}/hptt)
include_directories(${PROJECT_SOURCE_DIR}/tcl)

add_subdirectory("hptt")
add_subdirectory("tcl")

add_executable(contraction contraction.cpp)
target_link_libraries(contraction hptt tcl)

add_library(tcl_wrapper MODULE tcl_wrapper.cpp)
target_link_libraries(tcl_wrapper hptt tcl)
set_target_properties(tcl_wrapper PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

install(TARGETS contraction
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

install(TARGETS tcl_wrapper
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
