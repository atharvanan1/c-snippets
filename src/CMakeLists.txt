add_executable(Dummy main.c)
add_subdirectory(c_string)
add_subdirectory(prime)

target_link_libraries(Dummy PUBLIC
                            c_string_lib
                            prime_lib)

target_include_directories(Dummy PUBLIC
                            "${PROJECT_BINARY_DIR}"
                            "${PROJECT_SOURCE_DIR}/c_string"
                            "${PROJECT_SOURCE_DIR}/prime"
                            )
