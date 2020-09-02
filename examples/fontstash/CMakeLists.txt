find_package(SDL REQUIRED)
add_executable(sdlexample sdlexample.c)
target_link_libraries(sdlexample ${SDL_LIBRARY} osmesa ${M_LIBRARY} )
set_property(TARGET sdlexample APPEND PROPERTY COMPILE_DEFINITIONS "GL_DLL_IMPORTS")
if (O3_COMPILER_FLAG)
	# If we have the O3 flag, use it
	target_compile_options(sdlexample PRIVATE "-O3")
endif (O3_COMPILER_FLAG)

