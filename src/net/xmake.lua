target("net")
    set_kind("shared")
    add_includedirs("include", { public = true })
    add_files("*.cpp")
    add_defines("SHARED_LIB")
    if is_plat("windows") then
        add_defines("WIN32", "_WIN32", "DLLEXPORT")
    end
