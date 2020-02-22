cmake_minimum_required(VERSION 3.0)
set (CMAKE_CXX_STANDARD 11)
project(eraser)

include(.conan/conanbuildinfo.cmake)
conan_basic_setup()

set(SOURCES_FILES main.cpp game_window.cpp level_manager.cpp level.cpp spike.cpp plantivorus.cpp arachne.cpp ghost.cpp monster.cpp time_bonus.cpp player.cpp menu.cpp menu_button.cpp door.cpp pencil.cpp mouse_cursor.cpp position.cpp)
add_executable(eraser ${SOURCES_FILES})

file(COPY assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY data DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
target_link_libraries(eraser ${CONAN_LIBS})