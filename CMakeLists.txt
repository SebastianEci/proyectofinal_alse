cmake_minimum_required( VERSION 3.10 )
project( final_Alse )
add_executable( ${PROJECT_NAME} main.cpp sensor.h conteomedidas.cpp conteomedidas.h)

target_link_libraries (${PROJECT_NAME} sqlite3 )
