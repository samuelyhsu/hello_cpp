find_package(Eigen3 REQUIRED)
find_package(spdlog REQUIRED)
find_package(Catch2 REQUIRED)

function(def_test TARGET_NAME)
    add_executable(${TARGET_NAME} ${TARGET_NAME}.cpp)
    target_link_libraries(${TARGET_NAME} PRIVATE Eigen3::Eigen spdlog::spdlog Catch2::Catch2WithMain)
    add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME})
endfunction()

def_test(test_eigen)

def_test(test_cmath)

def_test(test_catch2)
