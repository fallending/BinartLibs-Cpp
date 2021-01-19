PROJECT(test1)
# PROJECT(projectname [CXX] [C] [Java])


SET(SRC_FILES main.cpp)


# MESSAGE指令的语法是：
# MESSAGE([SEND_ERROR | STATUS | FATAL_ERROR] "message to display"...)
# 这个指令用于向终端输出用户定义的信息，包含了三种类型:

# SEND_ERROR，产生错误，生成过程被跳过。
# SATUS，输出前缀为—的信息。
# FATAL_ERROR，立即终止所有cmake过程。
# 我们在这里使用的是STATUS信息输出，演示了由PROJECT指令定义的两个隐式变量HELLO_BINARY_DIR和HELLO_SOURCE_DIR。
MESSAGE(STATUS "This is BINARY dir " ${test1_BINARY_DIR})
MESSAGE(STATUS "This is SOURCE dir "${test1_SOURCE_DIR})

# 你可以用这个指令定义工程名称，并可指定工程支持的语言，支持的语言列表是可以忽略的，这个指令隐式的定义了两个cmake变量:

# <projectname>_BINARY_DIR 以及 <projectname>_SOURCE_DIR，这里就是 HELLO_BINARY_DIR 和 HELLO_SOURCE_DIR (所以CMakeLists.txt中两个MESSAGE指令可以直接使用了这两个变量)，因为采用的是内部编译，两个变量目前指的都是工程所在路径/backup/cmake/t1，后面我们会讲到外部编译，两者所指代的内容会有所不同。

# 同时cmake系统也帮助我们预定义了 PROJECT_BINARY_DIR 和 PROJECT_SOURCE_DIR 变量，他们的值分别跟 HELLO_BINARY_DIR 与 HELLO_SOURCE_DIR 一致。

# 为了统一起见，建议以后直接使用 PROJECT_BINARY_DIR，PROJECT_SOURCE_DIR，即使修改了工程名称，也不会影响这两个变量。如果使用了<projectname>_SOURCE_DIR，修改工程名称后，需要同时修改这些变量。



ADD_EXECUTABLE(hello ${SRC_FILES})


# message 的效果
# cmake ..
# CMake Warning (dev) at CMakeLists.txt:4:
#   Syntax Warning in cmake code at column 37

#   Argument not separated from preceding token by whitespace.
# This warning is for project developers.  Use -Wno-dev to suppress it.

# -- The C compiler identification is AppleClang 12.0.0.12000032
# -- The CXX compiler identification is AppleClang 12.0.0.12000032
# -- Check for working C compiler: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc
# -- Check for working C compiler: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc - works
# -- Detecting C compiler ABI info
# -- Detecting C compiler ABI info - done
# -- Detecting C compile features
# -- Detecting C compile features - done
# -- Check for working CXX compiler: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++
# -- Check for working CXX compiler: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ - works
# -- Detecting CXX compiler ABI info
# -- Detecting CXX compiler ABI info - done
# -- Detecting CXX compile features
# -- Detecting CXX compile features - done
# -- This is BINARY dir /Users/lilithgames/Desktop/binarts/BinartCppLibs/temp/test1/build
# -- This is SOURCE dir /Users/lilithgames/Desktop/binarts/BinartCppLibs/temp/test1
# -- Configuring done
# -- Generating done
# -- Build files have been written to: /Users/lilithgames/Desktop/binarts/BinartCppLibs/temp/test1/build


###############
# 也可以这么写!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

# PROJECT(hello)                                             #定义整个CMake的工程名
# FILE(GLOB SOURCE "./*.cpp")                      #告诉CMake：工程的源文件在哪里？
# ADD_EXECUTABLE(hello ${SOURCE})         #告诉CMake：我们要生成可执行文件（hello），并且源文件是由上面定义的