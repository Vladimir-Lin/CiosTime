SOURCES += $${PWD}/*.hpp
SOURCES += $${PWD}/*.cpp
SOURCES += $${PWD}/*.h
SOURCES += $${PWD}/*.c
SOURCES += $${PWD}/*.bat
SOURCES += $${PWD}/*.php
SOURCES += $${PWD}/*.js
SOURCES += $${PWD}/*.css
SOURCES += $${PWD}/*.html
SOURCES += $${PWD}/*.txt
SOURCES += $${PWD}/*.json
SOURCES += $${PWD}/*.xml
SOURCES += $${PWD}/*.py
SOURCES += $${PWD}/*.pl
SOURCES += $${PWD}/*.rb
SOURCES += $${PWD}/*.rs
SOURCES += $${PWD}/*.i

include ($${PWD}/Windows/Windows.pri)
include ($${PWD}/Mac/Mac.pri)
include ($${PWD}/Linux/Linux.pri)
