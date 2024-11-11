cmake_minimum_required(VERSION 3.20)
project(matrix_project)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(third_party)
add_subdirectory(src)

# Настройка GoogleTest
enable_testing()

# Найден GoogleTest
find_package(GTest REQUIRED)

# Создаем исполняемый файл для тестов
add_executable(unit_tests tests/unit_tests.cpp)

# Подключаем библиотеку matrix и GoogleTest
target_link_libraries(unit_tests PRIVATE matrix GTest::GTest GTest::Main)

# Добавляем тесты
add_test(NAME UnitTests COMMAND unit_tests)