add_executable(fontstash fontstash.c)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(fontstash ${SDL2_LIBRARIES} osmesa ${M_LIBRARY} )
set_property(TARGET fontstash APPEND PROPERTY COMPILE_DEFINITIONS "GL_DLL_IMPORTS")
if (O3_COMPILER_FLAG)
	# If we have the O3 flag, use it
	target_compile_options(fontstash PRIVATE "-O3")
endif (O3_COMPILER_FLAG)

