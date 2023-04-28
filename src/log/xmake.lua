package("spdlog")
    add_deps("cmake")
    set_sourcedir(path.join(os.scriptdir(), "spdlog"))
    on_install(function(package)
        local configs = {}
        table.insert(configs, "-DCMAKE_BUILD_TYPE=" .. (package:debug() and "Debug" or "Release"))
        table.insert(configs, "-DBUILD_SHARED_LIBS=" .. (package:config("shared") and "ON" or "OFF"))
        import("package.tools.cmake").install(package, configs)
    end)
    --on_test(function (package)
    --    assert(package:has_cfuncs("add", {includes = "foo.h"}))
    --end)
package_end()

add_requires("spdlog")

target("log")
    set_kind("static")
    add_files("*.cpp")
    add_includedirs("include", "spdlog/include", { public = true })
    if is_plat("windows") then
        add_defines("WIN32", "_WIN32", "DLLEXPORT")
    end
    add_packages("spdlog")
