cmake_minimum_required(VERSION 3.7)

project(space13)

message("Generating make!")

add_executable(${PROJECT_NAME} src/Main.cpp)

# Add SDL2
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ;SDL2)
find_package(SDL2 REQUIRED)
include_directories(${PROJECT_NAME} ${SDL2_INCLUDE_DIRS})

# Set SDL2_image_include_dirs
string(REPLACE "Space13/SDL2" "Space13/SDL2_image" SDL2_IMAGE_INCLUDE_DIRS "${SDL2_INCLUDE_DIRS}")
# This works off the assumption that the SDL2 and SDL2_image build structures are the same, which they currently are 

# Add SDL2_image
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ;SDL2_image)
set(WIN32 1) # FIXME: What the fuck, why
find_package(SDL2_image REQUIRED)
include_directories(${PROJECT_NAME} ${SDL2_IMAGE_INCLUDE_DIRS})



target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} SDL2_image::SDL2_image)



# RELEASE
# add_definitions(-O3 -std=c++20 -Wextra -Wall -Werror)

# DEBUG
add_definitions(-std=c++20 -Wextra -Wall -Werror -O0 -g)

#TODO: Add seperate RELEASE and DEBUG build modes
