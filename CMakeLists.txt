project(rpi-radio)
cmake_minimum_required(VERSION 2.6)

find_package(Qt4 REQUIRED QtCore QtGui QtDeclarative Phonon)

include_directories(${QT_INCLUDES} ${QT_PHONON_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR} include)

set(rpi-radio_HDRS include/Controls.h include/Button.h include/Encoder.h include/VolumeWidget.h include/ListWidget.h include/ClockWidget.h include/PlayerWidget.h include/GPIO.h include/rpi-radio.h)
set(rpi-radio_SRCS Controls.cpp Button.cpp Encoder.cpp VolumeWidget.cpp ListWidget.cpp ClockWidget.cpp PlayerWidget.cpp GPIO.cpp rpi-radio.cpp main.cpp)
qt4_wrap_cpp(rpi-radio_MOC ${rpi-radio_HDRS})
QT4_ADD_RESOURCES(rpi-radio_RESOURCES_RCC rpi-radio.qrc)
add_executable(rpi-radio ${rpi-radio_SRCS} ${rpi-radio_RESOURCES_RCC} ${rpi-radio_MOC})
target_link_libraries(rpi-radio ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTDECLARATIVE_LIBRARY} ${QT_PHONON_LIBRARY})
install(TARGETS rpi-radio RUNTIME DESTINATION bin)
