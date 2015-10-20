project(rpi-radio)
cmake_minimum_required(VERSION 2.6)

file(GLOB rpi-radio_HDRS include/*.h PJ_RPI/PJ_RPI.h)
file(GLOB rpi-radio_SRCS src/*.cpp PJ_RPI/PJ_RPI.c main.cpp)

find_package(Qt5Core QUIET)
if (DEFINED Qt5Core_INCLUDE_DIRS)
	find_package(Qt5Widgets REQUIRED)
	find_package(Qt5SerialPort REQUIRED)
	find_package(Qt5Multimedia REQUIRED)
	find_package(Qt5Declarative REQUIRED)
	set(QtIncDirs ${Qt5Core_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS} ${Qt5Declarative_INCLUDE_DIRS} ${Qt5Multimedia_INCLUDE_DIRS} ${Qt5Qml_INCLUDE_DIRS} ${Qt5Quick_INCLUDE_DIRS} ${Qt5SerialPort_INCLUDE_DIRS})
	set(QtLibs ${Qt5Core_LIBRARIES} ${Qt5Widgets_LIBRARIES} ${Qt5Declarative_LIBRARIES} ${Qt5Multimedia_LIBRARIES} ${Qt5Qml_LIBRARIES} ${Qt5Quick_LIBRARIES} ${Qt5SerialPort_LIBRARIES})
	QT5_WRAP_CPP(rpi-radio_MOC ${rpi-radio_HDRS})
	QT5_ADD_RESOURCES(rpi-radio_RESOURCES_RCC rpi-radio.qrc)
	set(HAVE_QT5 ${TRUE})
ELSE(DEFINED Qt5Core_INCLUDE_DIRS)
	find_package(Qt4 REQUIRED QtCore QtGui QtDeclarative QtNetwork Phonon)
	find_package(QtSerialPort REQUIRED)
	set(QtIncDirs ${QT_INCLUDES} ${QT_PHONON_INCLUDE_DIR} ${QtSerialPort_INCLUDE_DIR})
	set(QtLibs ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTDECLARATIVE_LIBRARY} ${QT_QTNETWORK_LIBRARY} ${QT_PHONON_LIBRARY} ${QtSerialPort_LIBRARY})
	QT4_WRAP_CPP(rpi-radio_MOC ${rpi-radio_HDRS})
	QT4_ADD_RESOURCES(rpi-radio_RESOURCES_RCC rpi-radio.qrc)
	set(HAVE_QT4 ${TRUE})
ENDIF(DEFINED Qt5Core_INCLUDE_DIRS)

include_directories(${QtIncDirs} ${CMAKE_CURRENT_BINARY_DIR} include PJ_RPI QtMtpClient)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -O2 -g -Wall -pthread -fstack-protector-all -Wstack-protector -Woverloaded-virtual -Wextra -Wshadow -Wsuggest-attribute=noreturn")

add_subdirectory(QtMtpClient)

add_executable(rpi-radio ${rpi-radio_SRCS} ${rpi-radio_RESOURCES_RCC} ${rpi-radio_MOC})
target_link_libraries(rpi-radio ${QtLibs} QtMpdClient)
install(TARGETS rpi-radio RUNTIME DESTINATION bin)
