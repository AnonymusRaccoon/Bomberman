# Usage:
# FIND_PACKAGE(raylib REQUIRED)
# [...]
# TARGET_LINK_LIBRARIES(target_name raylib)

CMAKE_MINIMUM_REQUIRED(VERSION 3.11)

if (NOT raylib_FOUND)
	INCLUDE(FetchContent)

	FetchContent_Declare(raylib URL https://github.com/raysan5/raylib/archive/1dd9fbae94cde2238e25df80958ea6edae6d5103.tar.gz)
	FetchContent_GetProperties(raylib)
	if (NOT raylib_POPULATED)
		SET(FETCHCONTENT_QUIET NO)
		FetchContent_Populate(raylib)
		SET(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
		if (EMSCRIPTEN)
			SET(PLATFORM Web)
		endif()
		ADD_SUBDIRECTORY(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
		SET(raylib_FOUND TRUE)
	endif()
endif()
