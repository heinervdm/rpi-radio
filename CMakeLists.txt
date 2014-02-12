project(rpi-radio)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED QtCore QtGui QtDeclarative)
find_package(QtSerialPort REQUIRED)
find_package(Phonon REQUIRED)

include_directories(${QT_INCLUDES} ${PHONON_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ${QtSerialPort_INCLUDE_DIRS})

set(rpi-radio_SRCS Encoder.cpp VolumeWidget.cpp ListWidget.cpp ClockWidget.cpp PlayerWidget.cpp GPIO.cpp rpi-radio.cpp main.cpp)
qt4_automoc(${rpi-radio_SRCS})
QT4_ADD_RESOURCES(rpi-radio_RESOURCES_RCC rpi-radio.qrc)
add_executable(rpi-radio ${rpi-radio_SRCS} ${rpi-radio_RESOURCES_RCC})
target_link_libraries(rpi-radio ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTDECLARATIVE_LIBRARY} ${PHONON_LIBRARY} ${QtSerialPort_LIBRARIES})
install(TARGETS rpi-radio RUNTIME DESTINATION bin)
