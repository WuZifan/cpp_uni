#################### Import the 'io_tools' library here ########################
find_library(TOOLS
             NAMES io_tools
             PATHS ${LIBRARY_OUTPUT_PATH})

#################### Create a library 'image' below this line ##################

add_library(image image.cpp)

# find_library(IMAGES
#              NAMES image
#              PATHS ${LIBRARY_OUTPUT_PATH} )


