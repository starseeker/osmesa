include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/../include
  ${CMAKE_CURRENT_SOURCE_DIR}/../src
  ${CMAKE_CURRENT_SOURCE_DIR}/glu/include
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

add_subdirectory(glu)

add_subdirectory(fontstash)


add_executable(osdemo osdemo.c)
target_link_libraries(osdemo osmesa glu ${M_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})
set_property(TARGET osdemo APPEND PROPERTY COMPILE_DEFINITIONS "GL_DLL_IMPORTS")

find_package(SDL)

if (SDL_FOUND)
  add_executable(texobj texobj.c)
  target_link_libraries(texobj osmesa ${SDL_LIBRARY} ${M_LIBRARY})
  set_property(TARGET texobj APPEND PROPERTY COMPILE_DEFINITIONS "GL_DLL_IMPORTS")
  if (O3_COMPILER_FLAG)
    # If we have the O3 flag, use it
    target_compile_options(texobj PRIVATE "-O3")
  endif (O3_COMPILER_FLAG)
  add_executable(gears gears.c)
  target_link_libraries(gears osmesa ${SDL_LIBRARY} ${M_LIBRARY})
  set_property(TARGET gears APPEND PROPERTY COMPILE_DEFINITIONS "GL_DLL_IMPORTS")
  if (O3_COMPILER_FLAG)
    # If we have the O3 flag, use it
    target_compile_options(gears PRIVATE "-O3")
  endif (O3_COMPILER_FLAG)
  add_executable(triangle triangle.c)
  target_link_libraries(triangle osmesa glu ${SDL_LIBRARY} ${M_LIBRARY})
  set_property(TARGET triangle APPEND PROPERTY COMPILE_DEFINITIONS "GL_DLL_IMPORTS")
  if (O3_COMPILER_FLAG)
    # If we have the O3 flag, use it
    target_compile_options(triangle PRIVATE "-O3")
  endif (O3_COMPILER_FLAG)
endif (SDL_FOUND)

find_package(TCL)
if (TCL_FOUND)
  include_directories(
    ${TCL_INCLUDE_PATH}
    )
  add_executable(tcltest tcl.cpp)
  target_link_libraries(tcltest osmesa ${TCL_LIBRARY} ${TK_LIBRARY} ${M_LIBRARY})
  set_property(TARGET tcltest APPEND PROPERTY COMPILE_DEFINITIONS "GL_DLL_IMPORTS")
endif (TCL_FOUND)


# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8
