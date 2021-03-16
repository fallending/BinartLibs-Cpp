<!--
 * @Author: your name
 * @Date: 2021-03-16 15:46:41
 * @LastEditTime: 2021-03-16 16:02:26
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /mt-ccs/doc/vcpkg.md
-->

# vcpkg


## vcpkg安装

> 看 bootstrap.sh

#### vcpkg 常用命令

```shell
D:\git\vcpkg>.\vcpkg --help
Commands:
  vcpkg search [pat]              Search for packages available to be built
  vcpkg install <pkg>...          Install a package
  vcpkg remove <pkg>...           Uninstall a package
  vcpkg remove --outdated         Uninstall all out-of-date packages
  vcpkg list                      List installed packages
  vcpkg update                    Display list of packages for updating
  vcpkg hash <file> [alg]         Hash a file by specific algorithm, default SHA512

  vcpkg integrate install         Make installed packages available user-wide. Requires admin privileges on first use
  vcpkg integrate remove          Remove user-wide integration
  vcpkg integrate project         Generate a referencing nuget package for individual VS project use

  vcpkg export <pkg>... [opt]...  Exports a package
  vcpkg edit <pkg>                Open up a port for editing (uses %EDITOR%, default 'code')
  vcpkg import <pkg>              Import a pre-built library
  vcpkg create <pkg> <url>
             [archivename]        Create a new package
  vcpkg owns <pat>                Search for files in installed packages
  vcpkg cache                     List cached compiled packages
  vcpkg version                   Display version information
  vcpkg contact                   Display contact information to send feedback

Options:
  --triplet <t>                   Specify the target architecture triplet.
                                  (default: %VCPKG_DEFAULT_TRIPLET%, see 'vcpkg help triplet')

  --vcpkg-root <path>             Specify the vcpkg root directory
                                  (default: %VCPKG_ROOT%)

For more help (including examples) see the accompanying README.md.
```

## vcpkg常用库安装

openssl, boost, zlib, glog, libevent, curl

## vcpkg 库制作

> 参考：https://blog.csdn.net/zieckey/article/details/72795427

#### 新建cmake工程，如 https://github.com/zieckey/vcpkgdemo

```
cmake_minimum_required(VERSION 3.8)

project (vcpkgdemo)

message(STATUS "This is BINARY dir " ${CMAKE_BINARY_DIR})
message(STATUS "This is SOURCE dir " ${CMAKE_SOURCE_DIR})

add_subdirectory(lib)
add_subdirectory(src bin)

# ----------------------------------------------------------------------------
# package information
set (CPACK_PACKAGE_VERSION_MAJOR    1)
set (CPACK_PACKAGE_VERSION_MINOR    2)
set (CPACK_PACKAGE_VERSION_PATCH    3)
set (CPACK_PACKAGE_CONTACT          "zieckey@gmail.com")
set (CPACK_GENERATOR                "TGZ")
set (CPACK_PACKAGING_INSTALL_PREFIX "/home/weizili/hello")

include (CPack)
```

#### 提交代码、打tag

如 https://github.com/zieckey/vcpkgdemo/archive/1.0.zip


#### vcpkg create 创建一个项目模板

```
D:\git\vcpkg>.\vcpkg create vcpkgdemo https://github.com/zieckey/vcpkgdemo/archive/1.0.zip vcpkgdemo-1.0.zip
-- Generated portfile: D:\git\vcpkg\ports\vcpkgdemo\portfile.cmake
-- Generated CONTROL: D:\git\vcpkg\ports\vcpkgdemo\CONTROL
-- To launch an editor for these new files, run
--     .\vcpkg edit vcpkgdemo
```

我们可以看到，在D:\git\vcpkg\ports\目录下多出一个vcpkgdemo目录，并且目录下有两个文件portfile.cmake和CONTROL。

#### 定制CONTROL文件

```
Source: vcpkgdemo
Version: 1.0
Description: A demo to show how to create a vcpkg package
```

#### 定制portfile.cmake文件

```
include(vcpkg_common_functions)
set(SOURCE_PATH ${CURRENT_BUILDTREES_DIR}/src/vcpkgdemo-1.0)
vcpkg_download_distfile(ARCHIVE
    URLS "https://github.com/zieckey/vcpkgdemo/archive/1.0.zip"
    FILENAME "vcpkgdemo-1.0.zip"
    SHA512 5b526b848c05d9b30eac8aede6c6c19591baf45e601c54ed6a0aa40ae3f11545d9648f332fb991f9540e44cfc3fc3ea6dd6db3b6c9d8e076b74af08e9ac69740
)

message(STATUS "Begin to extract files ...")
vcpkg_extract_source_archive(${ARCHIVE})

message(STATUS "Building vcpkgdemo project ...")

vcpkg_configure_cmake(
    SOURCE_PATH ${SOURCE_PATH}
    OPTIONS -DCMAKE_TOOLCHAIN_FILE=D:/git/vcpkg/scripts/buildsystems/vcpkg.cmake -DEVPP_VCPKG_BUILD=ON
)

vcpkg_install_cmake()
file(MAKE_DIRECTORY ${CURRENT_PACKAGES_DIR}/share)
file(MAKE_DIRECTORY ${CURRENT_PACKAGES_DIR}/share/vcpkgdemo)

#remove duplicated files
file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/debug/include)

# remove not used cmake files
file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/debug/share )
file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/debug/lib/cmake )
file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/lib/cmake )

# Handle copyright
file(COPY ${SOURCE_PATH}/LICENSE DESTINATION ${CURRENT_PACKAGES_DIR}/share/vcpkgdemo)
file(RENAME ${CURRENT_PACKAGES_DIR}/share/vcpkgdemo/LICENSE ${CURRENT_PACKAGES_DIR}/share/vcpkgdemo/copyright)

message(STATUS "Installing done")
```

这个时候，就可以本地 install 这个库了

```
.\vcpkg install vcpkgdemo
```

#### 库上传

将D:\git\vcpkg\ports\vcpkgdemo整个目录提交到https://github.com/Microsoft/vcpkg

也就是我们需要发起一个Pull Request到vcpkg的官方github地址 https://github.com/Microsoft/vcpkg

这里不再累述。

#### 上传后的库安装

然后可以通过命令.\vcpkg update .\vcpkg upgrade更新已经安装好的库。再通过install命令安装新的库。

#### 库的案例

evpp项目官网地址为：https://github.com/Qihoo360/evpp

为vcpkg制作的安装包，已经提交Pull Request ：https://github.com/Microsoft/vcpkg/pull/1177

vcpkgdemo的原始代码请见 https://github.com/zieckey/vcpkgdemo=