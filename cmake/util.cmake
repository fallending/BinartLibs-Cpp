# Copy files from source directory to destination directory, substituting any
# variables.  Create destination directory if it does not exist.

# With older CMake versions, this macro copies files from one directory to another. If you don't want to substitute variables in the copied files, then change the configure_file @ONLY argument (for example to COPYONLY).

# // https://stackoverflow.com/questions/697560/how-to-copy-directory-from-source-tree-to-binary-tree
macro(configure_files srcDir destDir)
    message(STATUS "Configuring directory ${destDir}")
    make_directory(${destDir})

    file(GLOB templateFiles RELATIVE ${srcDir} ${srcDir}/*)
    foreach(templateFile ${templateFiles})
        set(srcTemplatePath ${srcDir}/${templateFile})
        if(NOT IS_DIRECTORY ${srcTemplatePath})
            message(STATUS "Configuring file ${templateFile}")
            configure_file(
                    ${srcTemplatePath}
                    ${destDir}/${templateFile}
                    @ONLY)
        endif(NOT IS_DIRECTORY ${srcTemplatePath})
    endforeach(templateFile)
endmacro(configure_files)




# 判断操作系统

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "FreeBSD")

ELSE ()
MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")


## 判断编译器
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
# using Clang
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
# using GCC
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
# using Intel C++
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
# using Visual Studio C++
endif()



###
# CMake的函数不支持返回值，所以用变量导出来实现
###
function(check_os)
    set(is_os_ios true PARENT_SCOPE)
endfunction()
check_os()
message(STATUS "is ios:  ${is_os_ios}")


# 也可以参考下面这个函数
function(AddToListFromFunction BinaryName OutVariable)
    if ("${${OutVariable}}" STREQUAL "")
        message(STATUS "1")
        set(${OutVariable} ${BinaryName} PARENT_SCOPE)
        message(STATUS "OutVariable: ${OutVariable} ${${OutVariable}}")
    else ()
        message(STATUS "2")
        set(${OutVariable} "${${OutVariable}}" "${BinaryName}" PARENT_SCOPE)
    endif ()
endfunction()
AddToListFromFunction(MyBinary1 MyTests)
AddToListFromFunction(MyBinary2 MyTests)
message(STATUS "MyTests Variable:  ${MyTests}")