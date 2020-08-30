include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/../include
  ${CMAKE_CURRENT_SOURCE_DIR}/../src
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

add_executable(osdemo osdemo.c)
target_link_libraries(osdemo swrast ${M_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})

find_package(SDL)

if (SDL_FOUND)
  #add_executable(texobj texobj.c)
  #target_link_libraries(texobj tinygl ${SDL_LIBRARY} ${M_LIBRARY})
  #add_executable(gears gears.c)
  #target_link_libraries(gears swrast ${SDL_LIBRARY} ${M_LIBRARY})
  #add_executable(triangle triangle.c)
  #target_link_libraries(triangle tinygl ${SDL_LIBRARY} ${M_LIBRARY})
endif (SDL_FOUND)

#find_package(TCL)
if (TCL_FOUND)
  include_directories(
    ${TCL_INCLUDE_PATH}
    )
  add_executable(tcltest tcl.cpp)
  target_link_libraries(tcltest tinygl ${TCL_LIBRARY} ${TK_LIBRARY} ${M_LIBRARY})
endif (TCL_FOUND)


# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8
