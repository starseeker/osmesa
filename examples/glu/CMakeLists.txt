include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}../include
  ${CMAKE_CURRENT_SOURCE_DIR}/../src/main
  ${CMAKE_CURRENT_SOURCE_DIR}/../src/glapi
  ${CMAKE_CURRENT_SOURCE_DIR}/../src/shader
  ${CMAKE_CURRENT_SOURCE_DIR}/../src/drivers/common
  ${CMAKE_CURRENT_SOURCE_DIR}/../src/tnl
  ${CMAKE_CURRENT_SOURCE_DIR}/../src/swrast
  ${CMAKE_CURRENT_SOURCE_DIR}/../src/swrast_setup
  ${CMAKE_CURRENT_SOURCE_DIR}/../src/shader/grammar
  ${CMAKE_CURRENT_SOURCE_DIR}/../src/shader/slang
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/libnurbs/internals
	${CMAKE_CURRENT_SOURCE_DIR}/libnurbs/interface
	${CMAKE_CURRENT_SOURCE_DIR}/libnurbs/nurbtess
	)

# Bundle the glu functionality as well
set(glu_srcs
  libutil/error.c
  libutil/glue.c
  libutil/mipmap.c
  libutil/project.c
  libutil/quad.c
  libutil/registry.c
  libtess/dict.c
  libtess/geom.c
  libtess/memalloc.c
  libtess/mesh.c
  libtess/normal.c
  libtess/priorityq.c
  libtess/render.c
  libtess/sweep.c
  libtess/tess.c
  libtess/tessmono.c
  libnurbs/interface/bezierEval.cc
  libnurbs/interface/bezierPatch.cc
  libnurbs/interface/bezierPatchMesh.cc
  libnurbs/interface/glcurveval.cc
  libnurbs/interface/glinterface.cc
  libnurbs/interface/glrenderer.cc
  libnurbs/interface/glsurfeval.cc
  libnurbs/interface/incurveeval.cc
  libnurbs/interface/insurfeval.cc
  libnurbs/internals/arc.cc
  libnurbs/internals/arcsorter.cc
  libnurbs/internals/arctess.cc
  libnurbs/internals/backend.cc
  libnurbs/internals/basiccrveval.cc
  libnurbs/internals/basicsurfeval.cc
  libnurbs/internals/bin.cc
  libnurbs/internals/bufpool.cc
  libnurbs/internals/cachingeval.cc
  libnurbs/internals/ccw.cc
  libnurbs/internals/coveandtiler.cc
  libnurbs/internals/curve.cc
  libnurbs/internals/curvelist.cc
  libnurbs/internals/curvesub.cc
  libnurbs/internals/dataTransform.cc
  libnurbs/internals/displaylist.cc
  libnurbs/internals/flist.cc
  libnurbs/internals/flistsorter.cc
  libnurbs/internals/hull.cc
  libnurbs/internals/intersect.cc
  libnurbs/internals/knotvector.cc
  libnurbs/internals/mapdesc.cc
  libnurbs/internals/mapdescv.cc
  libnurbs/internals/maplist.cc
  libnurbs/internals/mesher.cc
  libnurbs/internals/monoTriangulationBackend.cc
  libnurbs/internals/monotonizer.cc
  libnurbs/internals/mycode.cc
  libnurbs/internals/nurbsinterfac.cc
  libnurbs/internals/nurbstess.cc
  libnurbs/internals/patch.cc
  libnurbs/internals/patchlist.cc
  libnurbs/internals/quilt.cc
  libnurbs/internals/reader.cc
  libnurbs/internals/renderhints.cc
  libnurbs/internals/slicer.cc
  libnurbs/internals/sorter.cc
  libnurbs/internals/splitarcs.cc
  libnurbs/internals/subdivider.cc
  libnurbs/internals/tobezier.cc
  libnurbs/internals/trimline.cc
  libnurbs/internals/trimregion.cc
  libnurbs/internals/trimvertpool.cc
  libnurbs/internals/uarray.cc
  libnurbs/internals/varray.cc
  libnurbs/nurbtess/directedLine.cc
  libnurbs/nurbtess/gridWrap.cc
  libnurbs/nurbtess/monoChain.cc
  libnurbs/nurbtess/monoPolyPart.cc
  libnurbs/nurbtess/monoTriangulation.cc
  libnurbs/nurbtess/partitionX.cc
  libnurbs/nurbtess/partitionY.cc
  libnurbs/nurbtess/polyDBG.cc
  libnurbs/nurbtess/polyUtil.cc
  libnurbs/nurbtess/primitiveStream.cc
  libnurbs/nurbtess/quicksort.cc
  libnurbs/nurbtess/rectBlock.cc
  libnurbs/nurbtess/sampleComp.cc
  libnurbs/nurbtess/sampleCompBot.cc
  libnurbs/nurbtess/sampleCompRight.cc
  libnurbs/nurbtess/sampleCompTop.cc
  libnurbs/nurbtess/sampleMonoPoly.cc
  libnurbs/nurbtess/sampledLine.cc
  libnurbs/nurbtess/searchTree.cc
  )

add_library(glu SHARED ${glu_srcs})
set_property(TARGET glu APPEND PROPERTY COMPILE_DEFINITIONS "UTIL_ARCH_LITTLE_ENDIAN=1")
set_property(TARGET glu APPEND PROPERTY COMPILE_DEFINITIONS "LIBRARYBUILD")
set_property(TARGET glu APPEND PROPERTY COMPILE_DEFINITIONS "GL_DLL_EXPORTS")
set_property(TARGET glu APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS "GL_DLL_IMPORTS")
if (O3_COMPILER_FLAG)
  # If we have the O3 flag, use it
  target_compile_options(osmesa PRIVATE "-O3")
endif (O3_COMPILER_FLAG)

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

