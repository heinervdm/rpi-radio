project(rpi-radio)
cmake_minimum_required(VERSION 2.6)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Qml REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(Qt5SerialPort REQUIRED)
find_package(Qt5Multimedia REQUIRED)

include_directories(${Qt5Core_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS} ${Qt5Multimedia_INCLUDE_DIRS} ${Qt5Qml_INCLUDE_DIRS} ${Qt5Quick_INCLUDE_DIRS} ${Qt5SerialPort_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR} include)

set(rpi-radio_HDRS include/QmlControl.h include/Controls.h include/Button.h include/Encoder.h include/PlayerWidget.h include/GPIO.h include/StationObject.h)
set(rpi-radio_SRCS src/QmlControl.cpp src/Controls.cpp src/Button.cpp src/Encoder.cpp src/PlayerWidget.cpp src/GPIO.cpp src/StationObject.cpp main.cpp)

QT5_WRAP_CPP(rpi-radio_MOC ${rpi-radio_HDRS})
QT5_ADD_RESOURCES(rpi-radio_RESOURCES_RCC rpi-radio.qrc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -O2 -g -Wall -pthread -fstack-protector-all -Wstack-protector -Woverloaded-virtual -Wextra -Wshadow -Wsuggest-attribute=noreturn")

add_executable(rpi-radio ${rpi-radio_SRCS} ${rpi-radio_RESOURCES_RCC} ${rpi-radio_MOC})
target_link_libraries(rpi-radio ${Qt5Core_LIBRARIES} ${Qt5Widgets_LIBRARIES} ${Qt5Multimedia_LIBRARIES} ${Qt5Qml_LIBRARIES} ${Qt5Quick_LIBRARIES} ${Qt5SerialPort_LIBRARIES})
install(TARGETS rpi-radio RUNTIME DESTINATION bin)
