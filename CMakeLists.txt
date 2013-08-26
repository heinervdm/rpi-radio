project(rpi-radio)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(rpi-radio_SRCS rpi-radio.cpp main.cpp)
qt4_automoc(${rpi-radio_SRCS})
add_executable(rpi-radio ${rpi-radio_SRCS})
target_link_libraries(rpi-radio ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
install(TARGETS rpi-radio RUNTIME DESTINATION bin)
