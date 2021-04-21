set_languages("c++14")

add_requires("gtest")

target("tests")
    set_kind('binary')

    add_deps("json-static", "http-static")

    add_packages("gtest")

    add_files('json/*.cc')

    -- find_packages("vcpkg::zlib", "vcpkg::openssl")

    -- on_load(function (target)
    --     target:add(find_packages("vcpkg::zlib", "vcpkg::openssl", "vcpkg::gtest"))
    -- end)