add_executable(detect_and_add_cylinder_collision_object_demo src/detect_and_add_cylinder_collision_object_demo.cpp)

target_include_directories(detect_and_add_cylinder_collision_object_demo
    PUBLIC include)
target_link_libraries(detect_and_add_cylinder_collision_object_demo ${catkin_LIBRARIES})

ament_target_dependencies(detect_and_add_cylinder_collision_object_demo
    ${THIS_PACKAGE_INCLUDE_DEPENDS} Boost)

install(
TARGETS
    detect_and_add_cylinder_collision_object_demo
DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY bags launch
    DESTINATION share/${PROJECT_NAME}
)
