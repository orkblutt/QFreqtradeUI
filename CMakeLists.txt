cmake_minimum_required(VERSION 3.5)

project(freqtradeUI LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets Network REQUIRED)

add_executable(freqtradeUI
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    restclient.cpp
    restclient.h
    qjsontablemodel.cpp
    qjsontablemodel.h
    optionsdialog.cpp
    optionsdialog.h
    optionsdialog.ui
    buydialog.cpp
    buydialog.h
    buydialog.ui
    confviewerdialog.cpp
    confviewerdialog.h
    confviewerdialog.ui
    resources.qrc
    freqtrade.rc
  )

target_link_libraries(freqtradeUI PRIVATE Qt5::Widgets Qt5::Network)
