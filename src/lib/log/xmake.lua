add_requires("spdlog")

target("log", function()
    set_kind("static")

    add_packages("spdlog", {configs = {public = true}})

    add_files("*.cpp")
    add_includedirs("include", {public = true})

    if is_plat("windows") then
        add_defines("WIN32", "_WIN32", "DLLEXPORT")
    end

    add_deps("singleton")
end)
