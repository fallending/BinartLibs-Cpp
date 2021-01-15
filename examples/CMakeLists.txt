ADD_EXECUTABLE(main main.cpp)  # 编译主程序
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)  # 更改输出路径

INCLUDE_DIRECTORIES(BEFORE ${PROJECT_SOURCE_DIR}/lib)  # 设置查找文件路径

LINK_DIRECTORIES(${PROJECT_BINARY_DIR}/lib)  # 链接库路径，程序运行的时候也在这里找
####
#注意，实际应用中有时是要写绝对路径的，因为库被安装在默认文件夹下，而不是编译路径下；这个时候就要FIND_PATH()
## find_path(
#            <VAR>  # 用来保存搜到的路径，如果没搜索到，就是notfound
#            name | NAMES name1 [name2 ...]  # 要搜索的文件名
#            [PATHS path1 [path2 ... ENV var]])  # 在哪里搜索
TARGET_LINK_LIBRARIES(main libhello.so) # (或hello)，链接哪个库，
#### 
#注意，如果用全名就是去系统默认目录查找库，比如/usr/lib/，如果找不到，就会报错，例如“/usr/bin/ld: 找不到 -lhello”,如果要到LINK_DIRECTORIES指定目录找，就要用target名，比如hello_static(静态)或hello(动态)，之后如果把动态库移动，程序会无法运行。