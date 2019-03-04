# Author : Foxman A.K.A. Vladimir Lin <lin.vladimir@gmail.com>
# Lastest update : 2019/03/03 17:01

QT          -= gui
TARGET       = libstardate
TEMPLATE     = lib
DEFINES     += QT_DEPRECATED_WARNINGS
DEFINES     += EXPORT_LIBSTARDATE

SRCROOT      = ../
SRCPATH      = $$SRCROOT/src

INCLUDEPATH  = $$SRCROOT/include

HEADERS     += $$SRCROOT/include/stardate.hpp

SOURCES     += $$SRCPATH/stardate.cpp
SOURCES     += $$SRCPATH/startime.cpp
SOURCES     += $$SRCPATH/frequency.cpp
SOURCES     += $$SRCPATH/estimator.cpp
SOURCES     += $$SRCPATH/usleep.cpp
SOURCES     += $$SRCPATH/hardware.cpp

OTHER_FILES += $$SRCROOT/CMakeLists.txt
OTHER_FILES += $$SRCROOT/CiosTime.bat
OTHER_FILES += $$SRCROOT/install.bat
OTHER_FILES += $$SRCROOT/libstardate.pc.in
OTHER_FILES += $$SRCROOT/VERSION.txt

OTHER_FILES += $$SRCROOT/projects/*

OTHER_FILES += $$SRCROOT/docs/index.html
OTHER_FILES += $$SRCROOT/docs/*.txt
OTHER_FILES += $$SRCROOT/docs/tw/*
OTHER_FILES += $$SRCROOT/docs/en/*
OTHER_FILES += $$SRCROOT/docs/cn/*
OTHER_FILES += $$SRCROOT/docs/css/*.css

OTHER_FILES += $$SRCROOT/Html/en/*
OTHER_FILES += $$SRCROOT/Html/tw/*
OTHER_FILES += $$SRCROOT/Html/cn/*

OTHER_FILES += $$SRCROOT/JS/*
OTHER_FILES += $$SRCROOT/PHP/*
OTHER_FILES += $$SRCROOT/Python/*
OTHER_FILES += $$SRCROOT/Ruby/*
OTHER_FILES += $$SRCROOT/scripts/*
