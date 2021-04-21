
-- xmake 常用命令
-- xmake build targetname
-- xmake install targetname

-- target("x-mt-ccs")
--   set_kind("binary")
--   add_files("src//*.c") 

-- project
set_project("mtccs")

-- set xmake minimum version
set_xmakever("2.5.1")

-- set project version
set_version("1.6.6", {build = "%Y%m%d%H%M"})

-- set warning all as error
set_warnings("all", "error")

-- set language: c99
stdc = "c99"
set_languages(stdc)

-- add defines to config.h
set_configvar("_GNU_SOURCE", 1)
set_configvar("_REENTRANT", 1)

-- disable some compiler errors
add_cxflags("-Wno-error=deprecated-declarations", "-fno-strict-aliasing", "-Wno-error=expansion-to-defined")
add_mxflags("-Wno-error=deprecated-declarations", "-fno-strict-aliasing", "-Wno-error=expansion-to-defined")

-- add build modes
add_rules("mode.release", "mode.debug", "mode.profile", "mode.coverage")-- TODO, "mode.valgrind", "mode.asan", "mode.tsan", "mode.ubsan") -- for xmake v2.3.3
if is_mode("debug") then
    add_defines("__tb_debug__")
end
if is_mode("valgrind") then
    add_defines("__tb_valgrind__")
end
if is_mode("asan") then
    add_defines("__tb_sanitize_address__")
end
if is_mode("tsan") then
    add_defines("__tb_sanitize_thread__")
end

-- small or micro?
if has_config("small", "micro") then
  add_defines("__tb_small__")
  set_configvar("TB_CONFIG_SMALL", 1)
  if is_mode("release", "profile") then
      set_optimize("smallest")
  end
  add_cxflags("-fno-stack-protector")
end

-- for the windows platform (msvc)
if is_plat("windows") then
  add_defines("NOCRYPT", "NOGDI")
  if is_mode("debug") then
      add_cxflags("-Gs", "-RTC1")
      set_runtimes("MTd")
  else
      set_runtimes("MT")
  end
  add_syslinks("ws2_32")
elseif is_plat("android") then
  add_syslinks("m", "c")
elseif is_plat("mingw", "msys", "cygwin") then
  add_syslinks("ws2_32", "pthread", "m")
else
  add_syslinks("pthread", "dl", "m", "c")
end

-- enable backtrace symbols for linux
if is_plat("linux") and is_mode("debug") then
  add_ldflags("-rdynamic")
end

-- include project sources
includes("src")










-- the debug mode
if is_mode("debug") then
  -- enable the debug symbols
  set_symbols("debug")
  -- disable optimization
  set_optimize("none")
end
-- the release mode
if is_mode("release") then
  -- set the symbols visibility: hidden
  set_symbols("hidden")
  -- enable fastest optimization
  set_optimize("fastest")
  -- strip all symbols
  set_strip("all")
end

add_subdirs('src', 'tests')

option("hello")
  set_default(false)
  set_showmenu(true)
  add_defines("HELLO_ENABLE")

add_defines("DEBUG")

set_warnings("all", "error")
set_optimize("fastest")

target("test-sim")
  set_languages("c99", "cxx14")
  set_options("hello")
  set_kind("binary")
  add_files("tests/simple/*.cc")
  -- add_deps("library") -- target依赖
  add_packages("gtest", "openssl")
target_end()


