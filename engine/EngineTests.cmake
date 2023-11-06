# Add test files here
add_executable(engine_tests
        src/data_handler/file_handler/tests/file_reader_test.cc
        src/data_handler/file_handler/file_handler.cc
        src/data_handler/file_handler/file_handler.h

        include/entities/game_object.h
        src/entities/game_object.cc

        include/entities/transform.h
        src/entities/transform.cc

        include/entities/camera.h
        src/entities/camera.cc

        src/entities/tests/camera_test.cc
)

# Windows: Fetch GTest from repo
if (WIN32)
    include(FetchContent)
    FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    set(GTest_FOUND true)
else ()
    # UNIX: Look for package locally
    find_package(GTest)
endif (WIN32)

if (GTest_FOUND)
    enable_testing()
    target_compile_definitions(engine_tests PUBLIC MOCK_JSON="${CMAKE_CURRENT_SOURCE_DIR}/src/data_handler/file_handler/tests/mockfile.json")
    target_compile_features(engine_tests PUBLIC cxx_std_17)
    target_link_libraries(engine_tests nlohmann_json::nlohmann_json GTest::gtest_main)
    target_include_directories(engine_tests PUBLIC include)
    target_include_directories(engine_tests PRIVATE src)
    include(GoogleTest)
    add_test(AllTests engine_tests)
endif (GTest_FOUND)