add_rules("plugin.compile_commands.autoupdate", { outputdir = "build" })

set_languages("c++23")
set_policy("run.autobuild", true)
set_rundir("$(projectdir)") 

target("visual_sort")
    set_kind("binary")
    add_files("visual_sort/src/*.cpp")

target("hexdump")
    set_kind("binary")
    add_files("hexdump/src/*.cpp")

target("vector")
    set_kind("binary")
    add_files("vector/src/*.cpp")
