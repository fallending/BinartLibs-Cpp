
file(GLOB HDRS "./*.h")
file(GLOB SRCS "./mtjson/*.cc")

add_library(json STATIC ${SRCS})

target_include_directories(
  json
  PUBLIC
    "./mtjson/"
    "./rapidjson/"     
)

# 用于本地库依赖
# file(
#   COPY
#   "mtjson.h"
#   "mtjsontype.h"
#   "slothjson.h"
#   DESTINATION
#   "${CMAKE_BINARY_DIR}/../include/mtjson"
# )

# file(COPY "./rapidjson" DESTINATION "${CMAKE_BINARY_DIR}/../include/mtjson")

# 下面这么些，会导致头文件报错，找不到 rapidjson.h.......

# file(GLOB rapidjson_HDRS "rapidjson/error/*.h" "rapidjson/internal/*.h" "rapidjson/*.h")

# file(GLOB HDRS "./*.h")
# file(GLOB SRCS "./*.cpp")

# # 动态库、静态库

# add_library(mtjson-objs
#   OBJECT
#     ${SRCS}
#   )

# add_library(mtjson-shared # shared library
#   SHARED
#     $<TARGET_OBJECTS:mtjson-objs>
#   )

# set_target_properties(mtjson-shared
#   PROPERTIES
#     OUTPUT_NAME "mtjson"
#     CLEAN_DIRECT_OUTPUT 1
# )

# add_library(mtjson-static # static library
#   STATIC
#     $<TARGET_OBJECTS:mtjson-objs>
#   )

# set_target_properties(mtjson-static
#   PROPERTIES
#     OUTPUT_NAME "mtjson"
#     CLEAN_DIRECT_OUTPUT 1
#   )

# # 内部头文件依赖

# target_include_directories(
#   mtjson-static
#   PUBLIC
#     "rapidjson/"      
# )

# target_include_directories(
#   mtjson-shared
#   PUBLIC
#     "rapidjson/"      
# )

# # 用于本地库依赖
# file(
#   COPY
#   "mtjson.h"
#   "mtjsontype.h"
#   "slothjson.h"
#   ${rapidjson_HDRS}
#   DESTINATION
#   "${CMAKE_BINARY_DIR}/../include/mtjson"
# )

# ## 用于库最终部署
# install(TARGETS mtjson-shared mtjson-static 
#   LIBRARY DESTINATION mtjson
#   ARCHIVE DESTINATION mtjson)  # 静态库用archive关键字
# install(
#   FILES 
#   "mtjson.h"
#   "mtjsontype.h"
#   "slothjson.h" 
#   ${rapidjson_HDRS}
#   DESTINATION
#     mtjson
# )