# 注意：该库，只有头文件，，没有没有源文件
set (LIBNAME bitbuffer)

file(GLOB HDRS "*.hpp")

# 用于本地库依赖
file(
    COPY
        ${HDRS}
    DESTINATION
        ${PROJECT_SOURCE_DIR}/include/${LIBNAME}
)

## 用于库最终部署
install(
    FILES
        ${HDRS}
    DESTINATION 
        ${LIBNAME}
)