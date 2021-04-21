add_rules("mode.debug", "mode.release")

set_basename('json')
set_warnings("all", "error")
set_languages("c++14")

add_files("./mtjson/*.cc")

add_includedirs(".", {public = true})
add_includedirs("./mtjson", {public = true})
add_includedirs("./rapidjson", {public = true})

target("json-static")
  set_kind("static")
  
target("json-shared")
  set_kind("shared")