cmake_minimum_required( VERSION 3.10 )

set(CMAKE_TOOLCHAIN_FILE externals/vcpkg/scripts/buildsystems/vcpkg.cmake)
set(CMAKE_CXX_STANDARD 17)

project(NetworkClient)
#---------------------------------------------
#-- Client
#---------------------------------------------
set(PROJECT_NAME NetworkClient)

file(GLOB_RECURSE search_src_files 
	"*"
	)
	
message("search_src_files = ${search_src_files} ")

foreach(FILE ${search_src_files}) 
	get_filename_component(PARENT_DIR "${FILE}" PATH)
	file(RELATIVE_PATH PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} ${PARENT_DIR})
	string(REPLACE "/" "\\" GROUP "${PARENT_DIR}")
	set(GROUP "${GROUP}")
	source_group("${GROUP}" FILES "${FILE}")
endforeach()

add_executable(${PROJECT_NAME} ${search_src_files})
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)
#---------------------------------------------
#-- fmt
#---------------------------------------------
#add_subdirectory(fmt)
#set(fmt_DIR externals/fmt/_build)
find_package(fmt)

#---------------------------------------------
#-- imgui
#---------------------------------------------
find_package(imgui)

target_link_libraries(${PROJECT_NAME} fmt::fmt imgui::imgui)
