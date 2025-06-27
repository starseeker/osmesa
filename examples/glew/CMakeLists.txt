set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads)

if (Threads_FOUND)
  add_executable(glewinfo glew.c glewinfo.c)
  include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include
  )
  target_link_libraries(glewinfo osmesa Threads::Threads ${M_LIBRARY})
  set_property(TARGET glewinfo APPEND PROPERTY COMPILE_DEFINITIONS "GL_DLL_IMPORTS")
endif()

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8 cino=N-s
