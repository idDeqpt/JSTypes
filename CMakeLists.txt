cmake_minimum_required(VERSION 3.4.0)

set(PROJECT_NAME jstypes)

project(${PROJECT_NAME} CXX)
include_directories("./include")

set(SOURCE_LIB
	src/JSBoolean.cpp
	src/JSNumber.cpp
	src/JSString.cpp
	src/JSObject.cpp
	src/JSArray.cpp
	src/JSONParseError.cpp
	src/JSONParser.cpp)       

# Включение экспорта всех символов для создания динамической библиотеки
set (CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Создание динамической библиотеки с именем ${PROJECT_NAME}
add_library(${PROJECT_NAME} SHARED ${SOURCE_LIB})

set(dir ${CMAKE_CURRENT_SOURCE_DIR}/bin/)
set(EXECUTABLE_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)
set(LIBRARY_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir})
set(CMAKE_BUILD_FILES_DIRECTORY ${dir})
set(CMAKE_BUILD_DIRECTORY ${dir})
set(CMAKE_BINARY_DIR  ${dir})
SET(EXECUTABLE_OUTPUT_PATH ${dir})
SET(LIBRARY_OUTPUT_PATH ${dir}lib)
SET(CMAKE_CACHEFILE_DIR ${dir})