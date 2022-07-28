add_subdirectory(dltools)
include_directories(dltools)

# find_package(FreeImage
#             PATHS /opt/homebrew/Cellar/freeimage
#             REQUIRED)
# include_directories(${FreeImage_INCLUDE_DIRS})
# include_directories(/opt/homebrew/Cellar/freeimage/3.18.0/include)
# link_directories(/opt/homebrew/Cellar/freeimage/3.18.0/lib)
find_library(FreeImage
            NAMES freeimageplus.3
            PATHS /opt/homebrew/Cellar/freeimage/3.18.0/lib)

MESSAGE(${FreeImage})

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS}) # Not needed for CMake >= 2.8.11

ADD_EXECUTABLE(hello main.cpp)


target_link_libraries(hello ${OpenCV_LIBS} ${FreeImage} dltools)
# target_link_libraries(hel)