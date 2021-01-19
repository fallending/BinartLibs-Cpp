# 刚起步

## 需要思考的问题

- 源代码在哪里？
- 头文件在哪里？
- 怎么生成静态或者动态库？
- 程序链接的静态库在哪里？
- 如果工程的代码存放在很多地方，那又该怎么找到它们呢？

#### 这里推荐 tree 命令（谷歌搜索 tree 命令）

```
➜  build git:(master) ✗ tree .
.
├── CMakeCache.txt
├── CMakeFiles
│   ├── 3.17.3
│   │   ├── CMakeCCompiler.cmake
│   │   ├── CMakeCXXCompiler.cmake
│   │   ├── CMakeDetermineCompilerABI_C.bin
│   │   ├── CMakeDetermineCompilerABI_CXX.bin
│   │   ├── CMakeSystem.cmake
│   │   ├── CompilerIdC
│   │   │   ├── CMakeCCompilerId.c
│   │   │   ├── a.out
│   │   │   └── tmp
│   │   └── CompilerIdCXX
│   │       ├── CMakeCXXCompilerId.cpp
│   │       ├── a.out
│   │       └── tmp
│   ├── CMakeDirectoryInformation.cmake
│   ├── CMakeOutput.log
│   ├── CMakeTmp
│   ├── Makefile.cmake
│   ├── Makefile2
│   ├── TargetDirectories.txt
│   ├── cmake.check_cache
│   └── progress.marks
├── Makefile
├── bin
│   ├── CMakeFiles
│   │   ├── CMakeDirectoryInformation.cmake
│   │   ├── progress.marks
│   │   └── test1.dir
│   │       ├── C.includecache
│   │       ├── DependInfo.cmake
│   │       ├── build.make
│   │       ├── cmake_clean.cmake
│   │       ├── depend.internal
│   │       ├── depend.make
│   │       ├── flags.make
│   │       ├── link.txt
│   │       ├── main.o
│   │       └── progress.make
│   ├── Makefile
│   ├── cmake_install.cmake
│   └── test1
├── cmake_install.cmake
└── install_manifest.txt

10 directories, 35 files
```

## 规范

1. 命令用小写 (对应vscode插件: CMake)
2. 变量（局部、全局、环境变量）用大写
3. 具名参数用大写
