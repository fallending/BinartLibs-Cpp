
# file(GLOB rapidjson_HDRS "rapidjson/error/*.h" "rapidjson/internal/*.h" "rapidjson/*.h")

file(GLOB HDRS "./*.h" "./*.cpp")
file(GLOB SRCS "./*.cpp")

add_library(mtjson STATIC ${SRCS})

target_include_directories(
    mtjson
    PRIVATE
        "./rapidjson/"      
)

file(
  COPY
  "mtjson.h"
  "mtjsontype.h"
  DESTINATION
  "${CMAKE_BINARY_DIR}/../include/mtjson"
)