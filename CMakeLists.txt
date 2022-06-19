cmake_minimum_required(VERSION 3.18)

project(Dummy VERSION 0.1)
add_subdirectory(src)

configure_file(Config.h.in Config.h)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

option(BUILD_TEST "Build testing executables" OFF)
if(BUILD_TEST)
    # Testing framework
    include(FetchContent)
    FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    enable_testing()

    add_executable(
        c_snippets_test
        ${PROJECT_SOURCE_DIR}/tests/test_c_string.cpp
        ${PROJECT_SOURCE_DIR}/tests/test_memfunc.cpp
        ${PROJECT_SOURCE_DIR}/tests/test_linked_list.cpp
    )

    target_include_directories(
        c_snippets_test PUBLIC
        "${PROJECT_SOURCE_DIR}/src/c_string"
        "${PROJECT_SOURCE_DIR}/src/memfunc"
        "${PROJECT_SOURCE_DIR}/src/linked_list"
    )

    target_link_libraries(
        c_snippets_test
        gtest_main
        c_string_lib
        memfunc_lib
        linked_list_lib
    )

    include(GoogleTest)
    gtest_discover_tests(c_snippets_test)
endif()