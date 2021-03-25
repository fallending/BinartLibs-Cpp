set (CMAKE_CXX_STANDARD 14)
set (LIBNAME log)

file(GLOB
    HDRS 
    "*.h"
)
file(GLOB 
    SRCS
    "*.cc"
)

add_library(log
  STATIC
  ${SRCS}
)
