add_rules("mode.debug", "mode.release")

target("ifaddrs")
  set_kind("static")
  set_kind("shared")

  add_files("ifaddrs.c")

  set_warnings("all", "error")
