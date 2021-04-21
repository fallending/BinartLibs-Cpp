add_rules("mode.debug", "mode.release")

set_basename('http')
set_warnings("all", "error")
set_languages("c++14")

-- if is_os("ios") then
--   set_archs("x86_64", "arm64")
-- end

target("http-static")
  set_kind("static")
  
  add_files("http.cc")

  add_headerfiles("./*.h")

  if is_os("android") then
    add_includedirs("$(projectdir)/src/ifaddrs")
    add_links("ifaddrs")
  end
    
target("http-shared")
  set_kind("shared")

  add_files("http.cc")

  add_headerfiles("./*.h")

  -- if is_os("ios") then
  --   add_files("Info.plist")
  --   add_rules("xcode.framework")
  -- end

  if is_os("android") then
    add_includedirs("$(projectdir)/src/ifaddrs")
    add_links("ifaddrs")
  end