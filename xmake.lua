set_project("server")
set_version("0.1.0")
set_languages("cxx23")
set_toolchains("clang")
set_runtimes("c++_shared")
set_policy("build.c++.modules", true)

add_rules("mode.debug", "mode.release", "mode.releasedbg", "mode.check", "mode.profile")
add_rules("plugin.compile_commands.autoupdate", { lsp = "clangd", outputdir = "build" })

target("server", function()
	add_files("src/**.cpp")
end)
