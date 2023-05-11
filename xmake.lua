set_project("shadow")

add_configfiles("config.h.in")

-- version
set_version("0.0.1", {build = "%Y%m%d%H%M"})

-- set xmake min version
set_xmakever("2.2.3")

-- set warning all as error
--set_warnings("all", "error")

--set_toolchains("clang")

-- set language: c99, c++11
set_languages("c99", "cxx11")

add_rules("mode.debug", "mode.release")
if is_mode("release") then
    set_optimize("smallest")
    if is_plat("windows") then
        add_ldflags("/LTCG")
    end
end

add_requires("protobuf-cpp")

includes("src/**/xmake.lua")

add_includedirs("src/include")

target("shadow", function()
    set_kind("binary")
    add_files("src/*.cpp")

    add_packages("protobuf-cpp")
    add_files("proto/*.proto", {rules = "protobuf.cpp"})

    add_defines("SHARED_LIB")
    if is_plat("windows") then
        add_defines("WIN32", "_WIN32", "DLLEXPORT")
    end

    add_deps("log")
    add_deps("util")
    add_deps("luabridge")
    add_deps("net")
    add_deps("thread")
    add_deps("map")
end)
