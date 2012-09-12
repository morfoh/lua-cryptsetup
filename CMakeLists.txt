#
# Lua bindings for libcryptsetup
#
cmake_minimum_required(VERSION 2.8)

project(lua-cryptsetup C)

set(BUILD_SHARED_LIBS TRUE)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(INSTALL_CMOD share/lua/cmod CACHE PATH "Directory to install Lua binary modules (configure lua via LUA_CPATH)")

set(COMMON_CFLAGS "${CFLAGS}")
set(COMMON_LDFLAGS)
set(COMMON_LIBS)

## Lua 5.1.x
include(FindLua51)
if(NOT ${LUA51_FOUND})
    message(FATAL_ERROR "The FindLua51 module could not find lua :-(")
endif()
set(COMMON_LIBS "${COMMON_LIBS};${LUA_LIBRARIES}")

## LibCryptsetup
include(FindPkgConfig)
pkg_search_module(CRYPTSETUP REQUIRED libcryptsetup)
set(COMMON_CFLAGS "${COMMON_CFLAGS} ${CRYPTSETUP_CFLAGS}")
set(COMMON_LDFLAGS "${COMMON_LDFLAGS} ${CRYPTSETUP_LDFLAGS}")
set(COMMON_LIBS "${COMMON_LIBS};${CRYPTSETUP_LIBRARIES}")

## LuaNativeObjects
include(LuaNativeObjects)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${CMAKE_CURRENT_BINARY_DIR}
                    ${LUA_INCLUDE_DIR})

## LuaCryptsetup
set(LUA_CRYPTSETUP_SRC
	cryptsetup.nobj.lua
)

if(${USE_PRE_GENERATED_BINDINGS})
	set(LUA_CRYPTSETUP_SRC src/pre_generated-cryptsetup.nobj.c)
else()
	# Generate Lua bindings.
	GenLuaNativeObjects(LUA_CRYPTSETUP_SRC)
endif()

add_library(lua-cryptsetup MODULE ${LUA_CRYPTSETUP_SRC})
target_link_libraries(lua-cryptsetup ${COMMON_LIBS})
set_target_properties(lua-cryptsetup PROPERTIES PREFIX "")
set_target_properties(lua-cryptsetup PROPERTIES COMPILE_FLAGS "${COMMON_CFLAGS}")
set_target_properties(lua-cryptsetup PROPERTIES OUTPUT_NAME cryptsetup)

install(TARGETS lua-cryptsetup
        DESTINATION "${INSTALL_CMOD}")

