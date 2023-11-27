# Add test files here
add_executable(engine_tests
        src/data_handler/file_handler/file_handler.cc
        src/data_handler/file_handler/tests/file_handler_test.cc

        src/data_handler/serializer/tests/serializer_test.cc
        src/data_handler/serializer/json/nlohmann_json_serializer.cc
        src/data_handler/serializer/serializer.cc

        src/data_handler/data_object/tests/data_object_test.cc
        src/data_handler/data_object/data_object.cc

        src/input/input.cc
        include/entities/ui/ui_object.h
        src/entities/ui/ui_object.cc
        include/entities/scene/scene.h
        include/entities/scene/scene_background.h
        src/entities/scene/scene_object_registry.h
        include/entities/behaviour_script.h
        include/entities/game_object.h
        include/entities/transform.h
        include/entities/camera.h
        include/entities/sprite.h
        include/entities/animator.h
        include/entities/listeners/listener.h
        include/entities/listeners/key_listener.h
        include/entities/listeners/mouse_listener.h
        include/entities/structs/vector.h

        src/entities/scene/scene.cc
        src/entities/scene/scene_background.cc
        src/entities/scene/scene_object_registry.cc
        src/entities/behaviour_script.cc
        src/entities/scene/scene_manager.h
        src/entities/scene/scene_manager.cc
        src/entities/camera.cc
        src/entities/sprite.cc
        src/entities/animator.cc
        src/entities/transform.cc
        src/entities/game_object.cc
        src/entities/listeners/key_listener.cc
        src/entities/listeners/mouse_listener.cc
        src/entities/structs/tests/vector_test.cc

        include/entities/audio_source.h
        src/entities/audio_source.cc
        src/audio/audio.h
        src/audio/audio_factory.h
        src/audio/audio_factory_wrapper.h
        src/audio/audio_factory_wrapper.cc

        src/entities/tests/camera_test.cc
        src/entities/tests/animator_test.cc
        src/entities/scene/tests/scene_test.cc

        src/data_handler/data_object/builders/data_object_builder.cc
        src/data_handler/data_object/builders/data_object_builder.h
        src/entities/tests/game_object_test.cc

        src/utility/object_pool_test.cc
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
    target_compile_definitions(engine_tests PUBLIC MOCK_JSON="${CMAKE_CURRENT_SOURCE_DIR}src/data_handler/file_handler/tests/mockfile.json")
    target_compile_definitions(engine_tests PUBLIC MOCK_JSON_TEMP="${CMAKE_CURRENT_SOURCE_DIR}/src/data_handler/file_handler/tests/mocktwo.json")
    target_compile_features(engine_tests PUBLIC cxx_std_17)
    target_link_libraries(engine_tests engine nlohmann_json::nlohmann_json GTest::gtest_main GTest::gmock)
    target_include_directories(engine_tests PUBLIC ../include)
    target_include_directories(engine_tests PRIVATE ../src)
    include(GoogleTest)
    add_test(AllTests engine_tests)
endif (GTest_FOUND)