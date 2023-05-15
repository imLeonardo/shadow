target("singleton", function()
    set_kind("static")

    add_files("*.cpp")
    add_includedirs("include", {public = true})

    if is_plat("windows") then
        add_defines("WIN32", "_WIN32", "DLLEXPORT")
    end
end)
