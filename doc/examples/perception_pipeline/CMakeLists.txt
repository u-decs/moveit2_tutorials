# add_executable(cylinder_segment src/cylinder_segment.cpp)
# target_include_directories(cylinder_segment
#     PUBLIC include)
# target_link_libraries(cylinder_segment ${catkin_LIBRARIES})
# ament_target_dependencies(cylinder_segment
    # ${THIS_PACKAGE_INCLUDE_DEPENDS} Boost)

add_executable(cylinder_sub src/cylinder_sub.cpp)
target_include_directories(cylinder_sub
    PUBLIC include)
target_link_libraries(cylinder_sub ${catkin_LIBRARIES})
    ament_target_dependencies(cylinder_sub
    ${THIS_PACKAGE_INCLUDE_DEPENDS} Boost)

add_executable(bag_publisher_maintain_time src/bag_publisher_maintain_time.cpp)
target_include_directories(bag_publisher_maintain_time
    PUBLIC include)
target_link_libraries(bag_publisher_maintain_time ${catkin_LIBRARIES} ${Boost_LIBRARIES})
ament_target_dependencies(bag_publisher_maintain_time
    ${THIS_PACKAGE_INCLUDE_DEPENDS} Boost)

install(
TARGETS
    bag_publisher_maintain_time
    # cylinder_segment
    cylinder_sub
DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch
    DESTINATION share/${PROJECT_NAME}
)