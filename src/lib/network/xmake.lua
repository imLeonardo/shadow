add_requires("asio")

target("net", function()
    set_kind("shared")
    add_packages("asio")
    add_packages("spdlog")

    add_files("*.cpp")
    add_includedirs("include", {public = true})

    add_defines("SHARED_LIB")
    if is_plat("windows") then
        add_defines("WIN32", "_WIN32", "DLLEXPORT")
    end

    add_deps("singleton")
    add_deps("log")
    add_deps("configure")
end)
