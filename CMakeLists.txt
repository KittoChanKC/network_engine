cmake_minimum_required( VERSION 3.10 )

#---------------------------------------------
#-- NetworkWS (main)
#---------------------------------------------
project(NetworkWS)
set_property (DIRECTORY PROPERTY VS_STARTUP_PROJECT "NetworkWS")

file(GLOB_RECURSE search_src_files 
	"Source/include/*.*"
	"Source/src/*.*"
	)
	
message("search_src_files = ${search_src_files}")

foreach(FILE ${search_src_files}) 
	get_filename_component(PARENT_DIR "${FILE}" PATH)
	file(RELATIVE_PATH PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} ${PARENT_DIR})
	string(REPLACE "/" "\\" GROUP "${PARENT_DIR}")
	set(GROUP "${GROUP}")
	source_group("${GROUP}" FILES "${FILE}")
endforeach()
add_executable(NetworkWS ${search_src_files})

#---------------------------------------------
#-- fmt
#---------------------------------------------
#add_subdirectory(fmt)
set(fmt_DIR OpenSource/fmt/_build)
find_package(fmt)
target_link_libraries(NetworkWS fmt::fmt)
