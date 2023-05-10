# cmake_minimum_required(VERSION 3.0.0)

set(OOP_PROJECT_NAME
    oop
)
set(OOP_SOURCE_DIR
    src
)
set(OOP_SOURCE
    ${OOP_SOURCE_DIR}/main.cpp
)
set(OOP_LIBRARIES_DIR
    libs
)
set(OOP_LIBRARIES 
    array
    console
    menu
)

project(${OOP_PROJECT_NAME})

###########
# Project #
###########
add_executable(${OOP_PROJECT_NAME} ${OOP_SOURCE})

foreach(LIBRARY ${OOP_LIBRARIES})
    add_subdirectory("${OOP_LIBRARIES_DIR}/${LIBRARY}")
endforeach(LIBRARY)
target_link_libraries(${OOP_PROJECT_NAME} ${OOP_LIBRARIES})
