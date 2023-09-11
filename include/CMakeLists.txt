set(OSMESA_HDRS
  OSMesa/gl.h
  OSMesa/glext.h
  OSMesa/osmesa.h
  OSMesa/gl_mangle.h
  )
install(FILES ${OSMESA_HDRS} DESTINATION include/OSMesa)

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8
