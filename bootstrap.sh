###
# @Author: your name
# @Date: 2021-03-09 15:56:46
# @LastEditTime: 2021-03-16 14:53:01
# @LastEditors: Please set LastEditors
# @Description: In User Settings Edit
# @FilePath: /mt-ccs/bootstrap.sh
###

# ##########################
# c/c++ 包管理
# vcpkg
# ##########################

curdir=${HOME}

# 它可以用于安装：vcpkg install opencv

# find_package(OpenCV REQUIRED)
# find_package(OpenCV 3.4.9 REQUIRED)

# target_link_libraries(target ${OpenCV_LIBS})
# target_link_libraries(lib PUBLIC ${OpenCV_LIBS})
# target_include_directories(lib PUBLIC ${OpenCV_INCLUDE_DIRS})

# cmake .. -DCMAKE_TOOLCHAIN_FILE=path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
vcpkg_dir=${curdir}/.cmake_modules/
vcpkg_path=${vcpkg_dir}/vcpkg/vcpkg
function install_vcpkg() {
  rm -rf ${vcpkg_dir} && mkdir -p ${vcpkg_dir} && cd ${vcpkg_dir}
  git clone https://github.com/Microsoft/vcpkg.git
  cd vcpkg
  ./bootstrap-vcpkg.sh

  # vcpkg
  # export VCPKG_HOME=/Users/seven/.cmake_modules/vcpkg/
  # export PATH=$PATH:$VCPKG_HOME

  # brew install pkg-config

  echo "Please insert ${vcpkg_dir} to your ~/.zshrc"
  echo "Then you can install packages like : "
  echo "[获取包安装列表] vcpkg list"
  echo "[搜过指定包发布列表] vcpkg search gtest"
  echo "[安装指定包列表] vcpkg install opencv gtest"

  # gtest
  # vcpkg install gtest
  # find_package(GTest CONFIG REQUIRED)
  # target_link_libraries(main PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)

  echo "[卸载指定包列表] vcpkg remove opencv gtest"
}

if [ ! -f "${vcpkg_path}" ]; then
  install_vcpkg
else
  echo "vcpkg installed."
fi

# ##########################
# vcpkg 安装该工程的依赖
# ##########################

# ##########################
# anaconda被大多数人所认为是一个python的科学计算环境，其实它也可以被用作c/c++虚拟环境的管理
# https://zhuanlan.zhihu.com/p/103219038
# conda
# ##########################

# ##########################
# 构建加速器
# ninja
# ##########################

ninja_path=/usr/local/bin/ninja
if [ ! -f "${vcpkg_path}" ]; then
  brew install ninja
else
  echo "ninja installed."
fi

# ##########################
# C++ 静态分析工具
# cppcheck
# http://cppcheck.sourceforge.net
# ##########################
# cppcheck_path=/usr/local/bin/cppcheck
# if [ ! -f "${cppcheck_path}" ]; then
#   brew install cppcheck
# else
#   echo "cppcheck installed."
# fi

# ##########################
# C++ lint工具 (只是个正则工具，不构建语法树，能力有限)
# cpplint
# ##########################
cd bin && chmod a+x update-cpplint.sh && ./update-cpplint.sh && chmod a+x cpplint.py
echo "cpplint updated."

# ##########################
# C++ 性能测试工具
# benchmark
# https://github.com/google/benchmark
# ##########################

# ##########################
# C++ ??
# codacy
# https://www.codacy.com/
# ##########################

# ##########################
# C++ ????
# Artistic Style
# https://sourceforge.net/projects/astyle/
# ##########################

# ##########################
# Clang 代码格式化, 规范代码的工具
# clang-format
# https://my.oschina.net/u/4369588/blog/4401497
# https://blog.csdn.net/weixin_39609623/article/details/102080465
# ##########################
# clangformat_path=/usr/local/bin/clang-format
# if [ ! -f "${clangformat_path}" ]; then
#   brew install clang-format
# else
#   echo "clang-format installed."
# fi

# ##########################
# Clang 代码规范检查工具 （解析语法树，稍微厉害一些）
# clang-tidy
# 联合 FileCheck????LLVM 中的工具？？？
# 下载llvm：https://releases.llvm.org/download.html
# vscode 插件：https://github.com/notskm/vscode-clang-tidy/issues/40
# ##########################
clangtidy_path=/usr/local/opt/llvm/bin/clang-tidy
if [ ! -f "${clangtidy_path}" ]; then
  # xcode-select --install
  # brew install --build-from-source python@3.9
  # brew install --build-from-source llvm
  brew install llvm
  ln -s "$(brew --prefix llvm)/bin/clang-tidy" "/usr/local/bin/clang-tidy"
  ln -s "$(brew --prefix llvm)/share/clang/run-clang-tidy.py" "/usr/local/bin/run-clang-tidy.py"
else
  echo "clang-tidy installed."
fi

# call OCLint <http://oclint.org> static analyzer
# oclint:
# 	oclint $(SRCS) -report-type html -enable-global-analysis -o oclint_report.html -max-priority-1=10000 -max-priority-2=10000 -max-priority-3=10000 -- -std=c++11 -Iinclude
# 	open oclint_report.html

# http://bit2tib.com/2018/07/11/format-tools-for-cpp/

# ##########################
# 高级 cmake 工具
# xmake
# https://github.com/maketea-tech/xmake
# https://xmake.io/#/home
# ##########################
xmake_path=/usr/local/bin/xmake
if [ ! -f "${xmake_path}" ]; then
  # curl -fsSL https://xmake.io/shget.text -o install_xmake.sh
  # chmod a+x install_xmake.sh
  # ./install_xmake.sh
  # rm -rf install_xmake.sh
  brew install xmake
else
  echo "xmake installed."
fi
