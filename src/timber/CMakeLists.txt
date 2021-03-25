
# 注意：该库，只有头文件，，没有没有源文件
set (LIBNAME timber)

file(GLOB HDRS "*.h")

## 用于库最终部署
install(
    FILES
        ${HDRS}
    DESTINATION 
        ${LIBNAME}
)