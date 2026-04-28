add_executable(example1 example1.cpp)
add_executable(example2 example2.cpp)

# Добавляем линковку с библиотекой print
target_link_libraries(example1 PRIVATE print formatter)
target_link_libraries(example2 PRIVATE print formatter_ex formatter)

install(TARGETS example1 example2
    RUNTIME DESTINATION bin
)
