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

include ($${PWD}/css/css.pri)

include ($${PWD}/tw/tw.pri)
include ($${PWD}/cn/cn.pri)
include ($${PWD}/en/en.pri)
