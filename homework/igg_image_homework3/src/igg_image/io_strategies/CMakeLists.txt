
# TODO: link strategies against needed libraries.
# include_directories(./)


# find_package(PNG REQUIRED)

set(LIBPNG /System/Volumes/Data/opt/homebrew/Cellar/libpng/1.6.37/lib/libpng16.16.dylib)
# find_library(LIBPNG 
#             NAMES png16.16
#             PATHS /System/Volumes/Data/opt/homebrew/Cellar/libpng/1.6.37/lib)
# find_library(LIBPNG++
#             NAMES )       
# message(STATUS ${LIBPNG})
include_directories(/opt/homebrew/Cellar/png++/0.2.10/include)
include_directories(/Users/zifanwu/opt/anaconda3/include/libpng16)


add_library(strategies
            # TODO: Add other files here when needed.
            png_strategy.cpp
            dummy_strategy.cpp)

target_link_libraries(strategies LIBPNG)

