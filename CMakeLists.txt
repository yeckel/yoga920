cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)
project(yoga920)

FIND_PACKAGE(Boost 1.40 COMPONENTS program_options REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

set(SOURCES main.cpp ec_access.cpp ec_access.h)
add_executable(${PROJECT_NAME}  ${SOURCES})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} LINK_PUBLIC ${Boost_LIBRARIES} )
