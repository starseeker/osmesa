include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/../include
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

set(swrast_srcs
  s_aaline.c
  s_aatriangle.c
  s_alpha.c
  s_atifragshader.c
  s_bitmap.c
  s_blend.c
  s_blit.c
  s_clear.c
  s_context.c
  s_copypix.c
  s_depth.c
  s_drawpix.c
  s_feedback.c
  s_fog.c
  s_fragprog.c
  s_lines.c
  s_logic.c
  s_masking.c
  s_points.c
  s_renderbuffer.c
  s_span.c
  s_stencil.c
  s_texcombine.c
  s_texfetch.c
  s_texfilter.c
  s_texrender.c
  s_texture.c
  s_triangle.c
  s_zoom.c
  osmesa.c
  )

add_library(swrast SHARED ${swrast_srcs})
install(TARGETS swrast
  RUNTIME DESTINATION ${BIN_DIR}
  LIBRARY DESTINATION ${LIB_DIR}
  ARCHIVE DESTINATION ${LIB_DIR})
target_compile_definitions(swrast PRIVATE UTIL_ARCH_LITTLE_ENDIAN=1)

if (BUILD_STATIC_LIBS)
  add_library(swrast-static STATIC ${swrast_srcs})
  install(TARGETS swrast-static
    RUNTIME DESTINATION ${BIN_DIR}
    LIBRARY DESTINATION ${LIB_DIR}
    ARCHIVE DESTINATION ${LIB_DIR})
endif (BUILD_STATIC_LIBS)

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

