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
