target("configure", function()
    set_kind("static")
    add_files("*.cpp")
    add_includedirs("include", {public = true})

    if is_plat("windows") then
        add_defines("WIN32", "_WIN32", "DLLEXPORT")
    end

    add_deps("singleton")
    add_deps("log")
    add_deps("util")
    add_deps("luabridge")

    add_packages("lua")
    add_packages("spdlog")
end)
