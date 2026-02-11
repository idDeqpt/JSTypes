cmake_minimum_required(VERSION 3.5.0)

set(PROJECT_NAME JSTypes)

project(${PROJECT_NAME}
	VERSION 1.0.0
	LANGUAGES CXX
)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

option(BUILD_SHARED_LIBS "Build shared library" ON)

set(PUBLIC_HEADER
	include/JSTypes/JSArray.hpp
	include/JSTypes/JSBaseType.hpp
	include/JSTypes/JSBoolean.hpp
	include/JSTypes/JSNumber.hpp
	include/JSTypes/JSObject.hpp
	include/JSTypes/JSONParseError.hpp
	include/JSTypes/JSONParser.hpp
	include/JSTypes/JSString.hpp
	include/JSTypes/JSTypes.hpp)

set(SOURCE_FILES
	src/JSArray.cpp
	src/JSBoolean.cpp
	src/JSNumber.cpp
	src/JSObject.cpp
	src/JSONParseError.cpp
	src/JSONParser.cpp
	src/JSString.cpp)

if (BUILD_SHARED_LIBS)
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
	add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
else()
	add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
endif()

target_include_directories(${PROJECT_NAME}
	PUBLIC 
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set_target_properties(${PROJECT_NAME} PROPERTIES
	VERSION ${PROJECT_VERSION}
	SOVERSION ${PROJECT_VERSION_MAJOR}
	EXPORT_NAME ${PROJECT_NAME}
)

configure_package_config_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
	"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
	INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY SameMajorVersion
)

install(
	TARGETS ${PROJECT_NAME}
	EXPORT ${PROJECT_NAME}Targets
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
	DIRECTORY include/${PROJECT_NAME}
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
	EXPORT ${PROJECT_NAME}Targets
	FILE ${PROJECT_NAME}Targets.cmake
	NAMESPACE ${PROJECT_NAME}::
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

install(
	FILES
		"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
		"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

export(
	EXPORT ${PROJECT_NAME}Targets
	FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake"
	NAMESPACE ${PROJECT_NAME}::
)