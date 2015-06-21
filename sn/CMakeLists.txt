add_library(smartnova
  Utility.cpp Program.cpp
  Drawable
  RegularPolygon)
if (APPLE)
  find_library(cf_framework CoreFoundation)
  find_library(cg_framework CoreGraphics)
  find_library(cv_framework CoreVideo)
  find_library(io_framework IOKit)
  find_library(ak_framework AppKit)
  target_link_libraries(smartnova json11 ${gllibs} ${cf_framework} ${cg_framework} ${cv_framework} ${ak_framework} ${io_framework})
else ()
  target_link_libraries(smartnova json11 ${gllibs})
endif (APPLE)
