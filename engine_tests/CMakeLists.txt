cmake_minimum_required(VERSION 3.22)
cmake_policy(SET CMP0135 NEW)

project(engine_tests)

set(CMAKE_CXX_STANDARD 17)

add_executable(engine_tests
        src/data_handler/data_object/data_object_test.cc
        src/data_handler/file_handler/file_handler_test.cc
        src/data_handler/serializer/serializer_test.cc

        src/entities/animator_test.cc
        src/entities/camera_test.cc
        src/entities/game_object_test.cc

        src/entities/scene/scene_test.cc
        src/entities/structs/vector_test.cc
        src/utility/object_pool_test.cc)

find_package(GTest)

if (GTest_FOUND)
    enable_testing()

    # Link testing library with GTest and our own engine
    target_link_libraries(${PROJECT_NAME} PRIVATE
            engine
            GTest::gtest_main
            GTest::gmock)

    # Set the include directory of the engine library
    target_include_directories(${PROJECT_NAME} PUBLIC
            ../engine/include)

    target_include_directories(${PROJECT_NAME} PRIVATE
            ../engine/src)

    # Add CMake environment variables here
    target_compile_definitions(${PROJECT_NAME} PUBLIC
            MOCK_JSON="${CMAKE_CURRENT_SOURCE_DIR}/src/data_handler/file_handler/mockfile.json")
    target_compile_definitions(${PROJECT_NAME} PUBLIC
            MOCK_JSON_TEMP="${CMAKE_CURRENT_SOURCE_DIR}/src/data_handler/file_handler/mockwrite.json")

    # Include the GTest library
    include(GoogleTest)
    add_test(AllTests ${PROJECT_NAME})
endif ()