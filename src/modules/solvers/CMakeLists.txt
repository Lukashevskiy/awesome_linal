add_library(solvers STATIC
    gauss_seidel/gauss_seidel.hpp
    simple_iteration/simple_iteration.hpp
)

target_link_libraries(solvers INTERFACE matrix)
target_include_directories(solvers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)

install(TARGETS solvers DESTINATION lib)
install(DIRECTORY ../include/ DESTINATION include)