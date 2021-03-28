set (LIBNAME timber)

file(GLOB HDRS "*.h")

## 用于库最终部署
install(
    FILES
        ${HDRS}
    DESTINATION 
        ${LIBNAME}
)