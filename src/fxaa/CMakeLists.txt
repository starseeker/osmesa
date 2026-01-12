include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/../../include
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

set(fxaa_srcs
  fxaa_cpu.c
  )

add_library(fxaa_cpu STATIC ${fxaa_srcs})
target_link_libraries(fxaa_cpu ${M_LIBRARY})

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8
