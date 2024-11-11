add_library(matrix STATIC
    matrix.hpp
    matrix.inl
)

target_include_directories(matrix PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_compile_features(matrix PRIVATE cxx_std_23)

install(TARGETS matrix DESTINATION lib)
install(DIRECTORY ../include/ DESTINATION include)