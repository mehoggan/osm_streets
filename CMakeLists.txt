cmake_minimum_required(VERSION 3.10.0)
project(ServeRobotics VERSION 0.1.0 LANGUAGES C CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
find_package(Protozero REQUIRED)
find_package(Osmium REQUIRED COMPONENTS io gdal proj)
find_package(PQXX REQUIRED)

if(NOT OSMIUM_FOUND)
  message(WARNING "Libosmium not found!\n")
endif()

if(NOT PQXX_FOUND)
  message(WARNING "libpqxx not found!\n")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(ServeRobotics main.cpp)

message(STATUS "PQXX_LIBRARY=${PQXX_LIBRARY}")

target_link_libraries(ServeRobotics
  ${PQXX_LIBRARY}
  ${OSMIUM_XML_LIBRARIES}
  ${OSMIUM_PBF_LIBRARIES}
  ${OSMIUM_IO_LIBRARIES}
  ${OSMIUM_LIBRARIES}
)
