include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/../include
  ${CMAKE_CURRENT_SOURCE_DIR}/../src
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

add_executable(osdemo osdemo.c)
target_link_libraries(osdemo osmesa ${M_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})
set_property(TARGET osdemo APPEND PROPERTY COMPILE_DEFINITIONS "GL_DLL_IMPORTS")

# TODO -see if we can adapt this as an example:
# https://github.com/danginsburg/opengles3-book/blob/master/Chapter_2/Hello_Triangle/Hello_Triangle.c

if (NOT OSMESA_NAME_MANGLING)
  add_subdirectory(glew)
endif()

# TODO - do a version of the Tcl multithreading test using FLTK and C++ threading
find_package(FLTK)
if (FLTK_FOUND)
  if(NOT TARGET fltk::fltk)
    add_library(fltk::fltk INTERFACE IMPORTED)
    set_target_properties(
      fltk::fltk
      PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES "${FLTK_INCLUDE_DIR}"
      INTERFACE_LINK_LIBRARIES "${FLTK_LIBRARIES}"
      )
  endif()

  add_executable(fltktest fltk.cpp)
  target_link_libraries(fltktest osmesa fltk::fltk ${M_LIBRARY})
  set_property(TARGET fltktest APPEND PROPERTY COMPILE_DEFINITIONS "GL_DLL_IMPORTS")

endif (FLTK_FOUND)

find_package(SDL2)
if (SDL2_FOUND)

  add_subdirectory(fontstash)

  add_executable(texobj texobj.c)
  include_directories(${SDL2_INCLUDE_DIRS})
  target_link_libraries(texobj osmesa ${SDL2_LIBRARIES} ${M_LIBRARY})
  set_property(TARGET texobj APPEND PROPERTY COMPILE_DEFINITIONS "GL_DLL_IMPORTS")
  if (O3_COMPILER_FLAG)
    # If we have the O3 flag, use it
    target_compile_options(texobj PRIVATE "-O3")
  endif (O3_COMPILER_FLAG)

  add_executable(gears gears.c)
  target_link_libraries(gears osmesa ${SDL2_LIBRARIES} ${M_LIBRARY})
  set_property(TARGET gears APPEND PROPERTY COMPILE_DEFINITIONS "GL_DLL_IMPORTS")
  if (O3_COMPILER_FLAG)
    # If we have the O3 flag, use it
    target_compile_options(gears PRIVATE "-O3")
  endif (O3_COMPILER_FLAG)

  add_executable(triangle triangle.c)
  target_link_libraries(triangle osmesa ${SDL2_LIBRARIES} ${M_LIBRARY})
  set_property(TARGET triangle APPEND PROPERTY COMPILE_DEFINITIONS "GL_DLL_IMPORTS")
  if (O3_COMPILER_FLAG)
    # If we have the O3 flag, use it
    target_compile_options(triangle PRIVATE "-O3")
  endif (O3_COMPILER_FLAG)

endif (SDL2_FOUND)

find_package(X11)
if (X11_FOUND)
  find_package(TCL)
  if (TCL_FOUND)
    include_directories(
      ${TCL_INCLUDE_PATH}
      ${X11_INCLUDE_DIR}
      )
    add_executable(tcltest tcl.cpp)
    target_link_libraries(tcltest osmesa ${TCL_LIBRARY} ${TK_LIBRARY} ${M_LIBRARY} ${X11_LIBRARIES})
    set_property(TARGET tcltest APPEND PROPERTY COMPILE_DEFINITIONS "GL_DLL_IMPORTS")
  endif (TCL_FOUND)
endif (X11_FOUND)

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8
