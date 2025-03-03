add_executable(move_group_interface_tutorial
    src/move_group_interface_tutorial.cpp)
add_executable(move_group_interface
    src/move_group_interface.cpp)
add_executable(move_group_interface_2
    src/move_group_interface_2.cpp)
add_executable(move_group_interface_3
    src/move_group_interface_3.cpp)
add_executable(move_group_interface_4
    src/move_group_interface_4.cpp)
add_executable(move_group_interface_5
    src/move_group_interface_5.cpp)

target_include_directories(move_group_interface_tutorial
    PUBLIC include)
target_include_directories(move_group_interface
    PUBLIC include)
target_include_directories(move_group_interface_2
    PUBLIC include)
target_include_directories(move_group_interface_3
    PUBLIC include)
target_include_directories(move_group_interface_4
    PUBLIC include)
target_include_directories(move_group_interface_5
    PUBLIC include)


ament_target_dependencies(move_group_interface_tutorial
    ${THIS_PACKAGE_INCLUDE_DEPENDS} Boost)
ament_target_dependencies(move_group_interface
    ${THIS_PACKAGE_INCLUDE_DEPENDS} Boost)
ament_target_dependencies(move_group_interface_2
    ${THIS_PACKAGE_INCLUDE_DEPENDS} Boost)
ament_target_dependencies(move_group_interface_3
    ${THIS_PACKAGE_INCLUDE_DEPENDS} Boost)
ament_target_dependencies(move_group_interface_4
    ${THIS_PACKAGE_INCLUDE_DEPENDS} Boost)
ament_target_dependencies(move_group_interface_5
    ${THIS_PACKAGE_INCLUDE_DEPENDS} Boost)

install(TARGETS move_group_interface move_group_interface_tutorial
move_group_interface_2 move_group_interface_3 move_group_interface_4 move_group_interface_5
  DESTINATION lib/${PROJECT_NAME}
)
install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)
