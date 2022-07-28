add_subdirectory(igg_image)
include_directories(igg_image)


add_executable(main main.cpp)

message(STATUS "hhhh" ${TOOLS} )
target_link_libraries(main ${TOOLS} image)
