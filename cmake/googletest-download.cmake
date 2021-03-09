# code copied from https://crascit.com/2015/07/25/cmake-gtest/
cmake_minimum_required(VERSION 3.6)

project(googletest-download NONE)

include(ExternalProject)

set (GTEST_GIT_URL https://github.com/google/googletest.git)
set (GTEST_GIT_TAG bd46f66754f11b5644913f6eb8a1900971f3e0ad)

ExternalProject_Add(
  googletest
  GIT_REPOSITORY ${GTEST_GIT_URL}
  GIT_TAG ${GTEST_GIT_TAG}
  GIT_PROGRESS ON

  SOURCE_DIR "@GOOGLETEST_DOWNLOAD_ROOT@/googletest-src"
  BINARY_DIR "@GOOGLETEST_DOWNLOAD_ROOT@/googletest-build"

  LOG_DOWNLOAD ON

  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  TEST_COMMAND ""
)