find_package(Eigen3 REQUIRED)
find_package(spdlog REQUIRED)

set(TARGET_NAME hello_signal)
add_executable(${TARGET_NAME} ${TARGET_NAME}.cpp)

set(TARGET_NAME hello_random)
add_executable(${TARGET_NAME} ${TARGET_NAME}.cpp)
target_link_libraries(${TARGET_NAME} PRIVATE spdlog::spdlog)

set(TARGET_NAME hello_eigen)
add_executable(${TARGET_NAME} ${TARGET_NAME}.cpp)
target_link_libraries(${TARGET_NAME} PRIVATE Eigen3::Eigen spdlog::spdlog)
