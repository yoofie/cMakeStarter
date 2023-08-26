cmake_minimum_required(VERSION 3.0)

project(cMakeStarter)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Debug")
endif()

set(CMAKE_CXX_STANDARD 17)

# Bring the headers, such as Student.h into the project
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Can manually add the sources using the set command as follows:
# set(SOURCES src/mainapp.cpp src/Student.cpp)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")

# However, the file(GLOB...) allows for wildcard additions:
file(GLOB_RECURSE SOURCES "src/**.cpp")
file(GLOB_RECURSE FLDR LIST_DIRECTORIES true "src/**")

# Exclude Filter
list(FILTER SOURCES EXCLUDE REGEX "${CMAKE_CURRENT_SOURCE_DIR}/Test/.*")

# Add source files.
file(GLOB_RECURSE SOURCE_FILES
	${CMAKE_SOURCE_DIR}/src/*.c
	${CMAKE_SOURCE_DIR}/src/*.cpp)

# Add header files.
file(GLOB_RECURSE HEADER_FILES
	${CMAKE_SOURCE_DIR}/src/*.h
	${CMAKE_SOURCE_DIR}/src/*.hpp)

# "/MP4"
# add_compile_options("/SUBSYSTEM:WINDOWS")
# add_link_options("/SUBSYSTEM:WINDOWS")
# add_compile_options("MAP" "/MP4" "/P" "/emittoolversioninfo:no")
add_compile_options("/diagnostics:caret")
add_compile_options("/bigobj")
add_compile_options("/Zi")
add_compile_options("/IGNORE:C4267")
add_compile_options("/IGNORE:C4244")
add_compile_options(-D_CRT_SECURE_NO_WARNINGS)

# add_link_options("/SUBSYSTEM:WINDOWS")
if(CMAKE_BUILD_TYPE EQUAL "Debug")
	add_compile_options("/DEBUG:FULL")
	add_link_options("/DEBUG:FULL")
endif()

# add_compile_definitions(DTRACY_ENABLE DTRACY_FIBERS)
set(bleh GLOB_RECURSE children ${curdir}/vendor/*)

include_directories(vendor/gl3w/GL)
include_directories(include
	src
	src/app
	src/utilities
	src/globals
	src/exampleCode
	src/main
	vendor
	vendor/json
	vendor/glew
	vendor/copper
	vendor/spdlog
	vendor/implot
	vendor/spdlog
	vendor/tracy
	vendor/magic_enum
	vendor/imnodes
	vendor/concurrentqueue
	vendor/parallel_hashmap
	vendor/dylib/include
	vendor/duckdb
	vendor/sqlite342
	vendor/hashlib
	vendor/asyncpp
	vendor/asyncpp/async++
)

set(TRACY_ENABLE false)
set(DUCKDB_ENABLE false)
set(SQLITE_ENABLE false)
set(ASYNCPP_LIB_ENABLE true)
set(HASHLIB_ENABLE false)

# ######################
# OUTPUT PATHS
# ######################
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "") # this is super important in order for cmake to include the vcpkg search/lib paths!
set(CMAKE_TOOLCHAIN_FILE "E:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "") # this is super important in order for cmake to include the vcpkg search/lib paths!

# ######################
# LINK OPTIONS
# ######################
# link_directories(${PROJECT_NAME} E:/vcpkg/installed/x64-windows-static/lib)

# ######################
# GENERATE EXE
# ######################
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCES})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)

set_target_properties(${PROJECT_NAME}
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
	ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/lib"
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
	LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/lib"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
	RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)

# ###############################################################
# LIBS
# ###############################################################
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/)
set(LIBBDIRR ${CMAKE_SOURCE_DIR}/lib/)


# ######################
# TRACY
# ######################
if(TRACY_ENABLE)
	add_library(tracy STATIC)

	# add_compile_definitions(DTRACY_ENABLE DTRACY_FIBERS)
	target_include_directories(tracy PUBLIC "vendor/tracy" "vendor/tracy")
	set_target_properties(tracy PROPERTIES
		INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/vendor/tracy"
		INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/vendor/tracy"
	)
	target_compile_definitions(tracy PUBLIC TRACY_ENABLE=1 TRACY_FIBERS)
	target_sources(
		tracy
		PRIVATE
		"vendor/tracy/TracyClient.cpp"
	)
	target_link_libraries(${PROJECT_NAME} tracy)
endif()

# ######################
# SQLITE
# ######################
if(SQLITE_ENABLE)
	add_library(sqlite342 STATIC)
	target_compile_definitions(sqlite342 PUBLIC -DENABLE_SQLITE)
	target_include_directories(sqlite342 PUBLIC "vendor/sqlite342" "vendor/sqlite342")
	set_target_properties(sqlite342 PROPERTIES
		INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/vendor/sqlite342"
		INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/vendor/sqlite342"
	)
	target_compile_definitions(sqlite342 PUBLIC SQLITE_ENABLE)
	target_sources(
		sqlite342
		PRIVATE

		# "vendor/sqlite342/shell.c"
		"vendor/sqlite342/sqlite3.c"
	)

	# target_link_options(sqlite342 PUBLIC /NODEFAULTLIB:LIBCMT)
	target_link_options(sqlite342 PUBLIC /NODEFAULTLIB:MSVCRT)
	target_link_libraries(${PROJECT_NAME} sqlite342)

	# endif()
	if(CMAKE_BUILD_TYPE EQUAL "Debug")
		set(CMAKE_CXX_FLAGS "/MT")
	endif()
endif()

# ######################
# DUCKDB
# ######################
if(DUCKDB_ENABLE)
	add_library(duckdb STATIC)

	# add_compile_definitions(DDUCKDB_ENABLE DTRACY_FIBERS)
	target_include_directories(duckdb PUBLIC "vendor/duckdb" "vendor/duckdb")
	set_target_properties(duckdb PROPERTIES
		INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/vendor/duckdb"
		INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/vendor/duckdb"
	)
	target_compile_definitions(duckdb PUBLIC DUCKDB_ENABLE=1 DUCKDB_BUILD_LIBRARY)
	target_sources(
		duckdb
		PRIVATE
		"vendor/duckdb/duckdb.cpp"
	)
	target_link_libraries(${PROJECT_NAME} duckdb WS2_32)
endif()

# ######################
# HASHLIB
# ######################
if(HASHLIB_ENABLE)
	add_library(hashlib STATIC)

	target_include_directories(hashlib PUBLIC "vendor/hashlib" "vendor/hashlib")
	set_target_properties(hashlib PROPERTIES
		INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/vendor/hashlib"
		INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/vendor/hashlib"
	)
	target_compile_definitions(hashlib PUBLIC HASHLIB=1)
	target_sources(
		hashlib
		PRIVATE
		"vendor/hashlib/crc32.cpp"

		# "vendor/hashlib/digest.cpp"
		"vendor/hashlib/keccak.cpp"
		"vendor/hashlib/md5.cpp"
		"vendor/hashlib/sha1.cpp"
		"vendor/hashlib/sha3.cpp"
		"vendor/hashlib/sha256.cpp"
	)
	target_link_libraries(${PROJECT_NAME} hashlib)
endif()

# ######################
# ASYNCPP
# ######################
if(ASYNCPP_LIB_ENABLE)
	add_library(asyncpp STATIC)
	target_include_directories(asyncpp PUBLIC "vendor/asyncpp/src" "vendor/asyncpp/async++")
	target_compile_definitions(asyncpp PUBLIC -DLIBASYNC_STATIC)
	target_sources(
		asyncpp
		PRIVATE
		"vendor/asyncpp/src/scheduler.cpp"
		"vendor/asyncpp/src/threadpool_scheduler.cpp"
	)

	# target_link_options(asyncpp PUBLIC /NODEFAULTLIB:MSVCRT)
	target_link_libraries(${PROJECT_NAME} asyncpp)
endif()


# ######################
# MESSAGES
# ######################

if(CMAKE_BUILD_TYPE EQUAL "DEBUG")
	message("debug mode")
endif()

# ######################
# MACROS
# ######################
MACRO(SUBDIRLIST result curdir)
	FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
	SET(dirlist "")

	FOREACH(child ${children})
		IF(IS_DIRECTORY ${curdir}/${child})
			LIST(APPEND dirlist ${child})
		ENDIF()
	ENDFOREACH()

	SET(${result} ${dirlist})
ENDMACRO()

# SUBDIRLIST(SUBDIRS ${CMAKE_SOURCE_DIR}/vendor)
#
# message(bleh = ${SUBDIRS})
# message(PROJECT_NAME = ${PROJECT_NAME})
# message(SUBDIRSS = ${SUBDIRS})
# message(SRC_FOLDERS = ${SRC_FOLDERS})
# message(FLDR = ${FLDR})

# foreach(i IN LISTS SOURCES)
# message("${i}")
# endforeach()

# https://cmake.org/cmake/help/latest/manual/cmake-commands.7.html
if(MSVC)
	# string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
	# string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
	string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
else(MSVC)
	set(Boost_USE_STATIC_LIBS ON)
	set(Boost_USE_STATIC_RUNTIME ON)
endif(MSVC)

# ######################
# MSVC SPECIFICS
# ######################
# Create virtual folders to make it look nicer in VS
if(MSVC_IDE)
	# Macro to preserve source files hierarchy in the IDE
	macro(GroupSources curdir)
		file(GLOB children RELATIVE ${PROJECT_SOURCE_DIR}/${curdir} ${PROJECT_SOURCE_DIR}/${curdir}/*)

		foreach(child ${children})
			if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${curdir}/${child})
				GroupSources(${curdir}/${child})
			else()
				string(REPLACE "/" "\\" groupname ${curdir})
				string(REPLACE "src" "Sources" groupname ${groupname})
				source_group(${groupname} FILES ${PROJECT_SOURCE_DIR}/${curdir}/${child})
			endif()
		endforeach()
	endmacro()

	# Run macro
	GroupSources(src)
endif()

# ######################
# POST BUILD ACTIONS
# ######################
# Copy dlls

# if(WIN32)
# add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
# COMMAND ${CMAKE_COMMAND} -E copy_directory
# "${PROJECT_SOURCE_DIR}/dox"
# $<TARGET_FILE_DIR:${PROJECT_NAME}>)
# endif()

# To nicely support folders in IDEs.
set_property(GLOBAL PROPERTY USE_FOLDERS TRUE)

# ######################
# BUILD VERSION INFO
# ######################
IF(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/.git)
	FIND_PACKAGE(Git)

	IF(GIT_FOUND)
		EXECUTE_PROCESS(
			COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
			WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
			OUTPUT_VARIABLE "GIT_BUILD_VERSION"
			ERROR_QUIET
			OUTPUT_STRIP_TRAILING_WHITESPACE)
		EXECUTE_PROCESS(
			COMMAND ${GIT_EXECUTABLE} describe --tags --always
			WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
			OUTPUT_VARIABLE "GIT_BUILD_VERSION_TAG"
			ERROR_QUIET
			OUTPUT_STRIP_TRAILING_WHITESPACE)
		MESSAGE(STATUS "Git version: ${GIT_BUILD_VERSION}")
		MESSAGE(STATUS "Git version tag: ${GIT_BUILD_VERSION_TAG}")
	ELSE(GIT_FOUND)
		SET(GIT_BUILD_VERSION 0)
		SET(GIT_BUILD_VERSION_TAG 0)
	ENDIF(GIT_FOUND)
ENDIF(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/.git)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/support/version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/src/main/version.h)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/support/launch.json.temp ${CMAKE_CURRENT_SOURCE_DIR}/.vscode/launch.json @ONLY)
