add_requires("lua")

target("luabridge", function()
    set_kind("shared")
    add_files("*.cpp")
    add_includedirs("include", {public = true})

    add_packages("lua")

    add_defines("SHARED_LIB")
    if is_plat("windows") then
        add_defines("WIN32", "_WIN32", "DLLEXPORT")
    end

    add_deps("log")
end)
