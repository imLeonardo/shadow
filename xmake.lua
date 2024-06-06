set_project("shadow")

add_configfiles("config.h.in")

-- version
set_version("0.0.1", {build = "%Y%m%d%H%M"})

-- set xmake min version
set_xmakever("2.2.3")

-- set warning all as error
--set_warnings("all", "error")

--set_toolchains("clang")

-- set language: c99, c++20
set_languages("cxx20")

add_rules("mode.debug", "mode.release")
if is_mode("release") then
    set_optimize("smallest")
    if is_plat("windows") then
        add_ldflags("/LTCG")
    end
end

--add_requires("protobuf-cpp")
--add_requires("readline")

target("shadow", function()
    set_kind("binary")

    includes("lib/**/xmake.lua")
    includes("src/**/xmake.lua")

    add_includedirs("src/include")
    add_files("src/*.cpp", "src/*.cppm")

    --add_packages("protobuf-cpp")
    --add_files("src/proto/**.proto", {rules = "protobuf.cpp", proto_path = "src/proto"})

    --add_packages("spdlog")
    --add_packages("quickjs")

    add_defines("SHARED_LIB")
    if is_plat("windows") then
        add_defines("WIN32", "_WIN32", "DLLEXPORT")
    end

    add_deps("singleton")
    add_deps("log")
    add_deps("jsmanager")
    add_deps("configure")
    add_deps("util")
    add_deps("net")
    add_deps("threadpool")
    --add_deps("map")

    after_build(function(target)
        --local outdir = "$(buildir)/$(plat)/$(arch)/$(mode)"
        --os.cp("conf", outdir)
        --os.cp("script", outdir)
    end)
end)

target("test", function()
    set_kind("binary")

    --add_includedirs("lib")
    --add_includedirs("test/src/include")
    add_files("test/src/*.cpp", "test/src/*.cppm")

    --add_packages("protobuf-cpp")
    --add_files("test/src/proto/**.proto", {rules = "protobuf.cpp", proto_path = "test/src/proto"})

    --add_defines("SHARED_LIB")
    if is_plat("windows") then
        add_defines("WIN32", "_WIN32", "DLLEXPORT")
    end

    after_build(function(target)
        --local outdir = "$(buildir)/$(plat)/$(arch)/$(mode)"
        --os.cp("conf", outdir)
        --os.cp("script", outdir)
    end)
end)
