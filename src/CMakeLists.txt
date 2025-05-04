add_executable(ServeRobotics main.cpp)

target_link_libraries(ServeRobotics
  ${PQXX_LIBRARY}
  ${OSMIUM_XML_LIBRARIES}
  ${OSMIUM_PBF_LIBRARIES}
  ${OSMIUM_IO_LIBRARIES}
  ${OSMIUM_LIBRARIES}
)
