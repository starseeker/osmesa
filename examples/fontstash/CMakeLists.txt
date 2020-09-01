find_package(SDL REQUIRED)
add_executable(sdlexample sdlexample.c)
target_link_libraries(sdlexample ${SDL_LIBRARY} osmesa ${M_LIBRARY} )

