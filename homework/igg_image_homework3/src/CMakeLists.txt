add_subdirectory(igg_image)
include_directories(igg_image)
include_directories(/Users/zifanwu/opt/anaconda3/include/libpng16)
include_directories(/opt/homebrew/Cellar/png++/0.2.10/include)
include_directories(/opt/homebrew/Cellar/png++/0.2.10/include/png++)


find_package(OpenCV 2 REQUIRED)

add_executable(main main.cpp)
target_link_libraries(main
                    ${LIBPNG}
                    strategies)
