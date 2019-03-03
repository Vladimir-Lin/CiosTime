# Author : Foxman A.K.A. Vladimir Lin <lin.vladimir@gmail.com>
# Lastest update : 2019/02/23 23:11

QT          -= gui
TARGET       = libnations
TEMPLATE     = lib
DEFINES     += QT_DEPRECATED_WARNINGS
DEFINES     += EXPORT_LIBNATIONS

SRCROOT      = ../
SRCPATH      = $$SRCROOT/src

INCLUDEPATH  = $$SRCROOT/include

HEADERS     += $$SRCROOT/include/nations.hpp

SOURCES     += $$SRCPATH/nation.cpp
SOURCES     += $$SRCPATH/region.cpp
SOURCES     += $$SRCPATH/countries.cpp
SOURCES     += $$SRCPATH/extended.cpp
SOURCES     += $$SRCPATH/enumerations.cpp

OTHER_FILES += $$SRCROOT/CMakeLists.txt
OTHER_FILES += $$SRCROOT/CiosNations.bat
OTHER_FILES += $$SRCROOT/install.bat
OTHER_FILES += $$SRCROOT/libnations.pc.in

OTHER_FILES += $$SRCROOT/projects/*

OTHER_FILES += $$SRCROOT/docs/index.html
OTHER_FILES += $$SRCROOT/docs/*.txt
OTHER_FILES += $$SRCROOT/docs/*.sql
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
