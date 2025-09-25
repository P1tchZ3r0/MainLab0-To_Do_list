QT += core widgets
CONFIG += c++17

TEMPLATE = app
TARGET = TodoList

SOURCES += \
    main.cpp \
    task.cpp \
    todolist.cpp \
    MainWindow.cpp 


HEADERS += \
    task.h \
    todolist.h \
    MainWindow.h 


# Установка кодировки
win32: QMAKE_CXXFLAGS += /utf-8