add_executable(Dummy main.c)
add_subdirectory(c_string)

target_link_libraries(Dummy PUBLIC c_string_lib)

target_include_directories(Dummy PUBLIC
                            "${PROJECT_BINARY_DIR}"
                            "${PROJECT_SOURCE_DIR}/c_string"
                            )
