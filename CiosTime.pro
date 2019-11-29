# CIOS Time Qt Creator Project File

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
SOURCES += $${PWD}/*.pc.in
SOURCES += $${PWD}/*.md

include ($${PWD}/docs/docs.pri)
include ($${PWD}/Html/Html.pri)
include ($${PWD}/include/include.pri)
include ($${PWD}/JS/JS.pri)
include ($${PWD}/PHP/PHP.pri)
include ($${PWD}/projects/projects.pri)
include ($${PWD}/Python/Python.pri)
include ($${PWD}/Ruby/Ruby.pri)
include ($${PWD}/scripts/scripts.pri)
include ($${PWD}/src/src.pri)

include ($${PWD}/Qt/libstardate.pro)
