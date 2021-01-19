PROJECT(test2)

# 1. 设置目标二进制保存路径

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# <projectname>_BINARY_DIR和PROJECT_BINARY_DIR变量：
# 分别定义了：可执行二进制的输出路径为build/bin和库的输出路径为build/lib.本节我们没有提到共享库和静态库的构建

# 所以，你可以不考虑第二条指令。
# 问题是，我应该把这两条指令写在工程的CMakeLists.txt还是src目录下的CMakeLists.txt，把握一个简单的原则，在哪里ADD_EXECUTABLE或ADD_LIBRARY，如果需要改变目标存放路径，就在哪里加入上述的定义。在这个例子里，当然就是指src下的CMakeLists.txt了。

ADD_SUBDIRECTORY(src bin)

# 安装COPYRIGHT/README，直接修改主工程文件CMakelists.txt，加入以下指令：
INSTALL(FILES COPYRIGHT README DESTINATION share/doc/cmake/test2)

# 安装runhello.sh，直接修改主工程文件CMakeLists.txt，加入如下指令：
INSTALL(PROGRAMS runtest2.sh DESTINATION bin)

# 安装doc中的hello.txt，这里有两种方式：
# 一是通过在doc目录建立 CMakeLists.txt并将doc目录通过ADD_SUBDIRECTORY加入工程来完成。
# 另一种方法是直接在工程目录通过 INSTALL(DIRECTORY来完成)，前者比较简单，各位可以根据兴趣自己完成，我们来尝试后者，顺便演示以下DIRECTORY的安装。因为hello.txt要安装到/<prefix>/share/doc/cmake/t2，所以我们不能直接安装整个doc目录，这里采用的方式是安装doc目录中的内容，也就是使用”doc/”在工程文件中添加
INSTALL(DIRECTORY doc/ DESTINATION share/doc/cmake/t2)

# 2. 打包时指定目录安装
# cmake -DCMAKE_INSTALL_PREFIX=../outputs ..

# 安装指令定义如下
# 默认安装: 如果我没有定义CMAKE_INSTALL_PREFIX会安装到什么地方？你可以尝试以下，cmake ..;make;make install，你会发现CMAKE_INSTALL_PREFIX的默认定义是/usr/local

# 指令用于定义安装规则，安装的内容可以包括目标二进制、动态库、静态库以及文件、目录、脚本等。
  # INSTALL(TARGETS targets... 
  # [[ARCHIVE|LIBRARY|RUNTIME] # 通过ADD_EXECUTABLE或者ADD_LIBRARY定义的目标文件，可能是可执行二进制、动态库、静态库。目标类型也就相对应的有三种，ARCHIVE特指静态库，LIBRARY特指动态库，RUNTIME特指可执行目标二进制。
  # [DESTINATION <dir>] # 定义了安装的路径，如果路径以/开头，那么指的是绝对路径，这时候CMAKE_INSTALL_PREFIX其实就无效了
  # [PERMISSIONS permissions...]
  # [CONFIGURATIONS
  # [Debug|Release|...]]
  # [COMPONENT <component>]
  # [OPTIONAL]
  # ] [...])

# 这里 DESTINATION 和 CMAKE_INSTALL_PREFIX 冲突了。

# 库安装：举例子

# INSTALL(TARGETS myrun mylib mystaticlib
# RUNTIME DESTINATION bin
# LIBRARY DESTINATION lib
# ARCHIVE DESTINATION libstatic
# )

# 解释：可执行二进制myrun安装到${CMAKE_INSTALL_PREFIX}/bin目录动态库libmylib安装到${CMAKE_INSTALL_PREFIX}/lib目录，静态库libmystaticlib安装到${CMAKE_INSTALL_PREFIX}/libstatic目录，特别注意的是：你不需要关心TARGETS具体生成的路径，只需要写上TARGETS名称就可以了。


# 普通文件的安装
# INSTALL(FILES files... DESTINATION <dir>
# [PERMISSIONS permissions...]
# [CONFIGURATIONS [Debug|Release|...]]
# [COMPONENT <component>]
# [RENAME <name>] [OPTIONAL])

# 非目标文件的可执行程序安装(比如脚本之类)：

# INSTALL(PROGRAMS files... DESTINATION <dir>
# [PERMISSIONS permissions...]
# [CONFIGURATIONS [Debug|Release|...]]
# [COMPONENT <component>]
# [RENAME <name>] [OPTIONAL])

# 目录的安装：

# INSTALL(DIRECTORY dirs... DESTINATION <dir>
# [FILE_PERMISSIONS permissions...]
# [DIRECTORY_PERMISSIONS permissions...]
# [USE_SOURCE_PERMISSIONS]
# [CONFIGURATIONS [Debug|Release|...]]
# [COMPONENT <component>]
# [[PATTERN <pattern> | REGEX <regex>]
# [EXCLUDE] [PERMISSIONS permissions...]] [...])

# 目录安装的例子

# INSTALL(DIRECTORY icons scripts/ DESTINATION share/myproj
# PATTERN "CVS" EXCLUDE
# PATTERN "scripts/*"
# PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
# GROUP_EXECUTE GROUP_READ)

# 安装时CMAKE脚本的执行：

# INSTALL([[SCRIPT <file>] [CODE <code>]] [...])
# SCRIPT参数用于在安装时调用cmake脚本文件（也就是<abc>.cmake文件）
# CODE参数用于执行CMAKE指令，必须以双引号括起来。比如：
# INSTALL(CODE "MESSAGE(\"Sample install message.\")")
# 安装还有几个被标记为过时的指令，比如INSTALL_FILES等，这些指令已经不再推荐使用，所以，这里就不再赘述了。下面，我们就来改写我们的工程文件，让他来支持各种文件的安装，并且，我们要使用CMAKE_INSTALL_PREFIX指令。