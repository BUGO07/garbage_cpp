add_rules("plugin.compile_commands.autoupdate", { outputdir = "build" })

set_languages("c++23")
set_policy("run.autobuild", true)

target("visual_sort")
    set_kind("binary")
    add_files("visual_sort/src/*.cpp")
    set_rundir("$(projectdir)") 

target("hexdump")
    set_kind("binary")
    add_files("hexdump/src/*.cpp")
    set_rundir("$(projectdir)") 