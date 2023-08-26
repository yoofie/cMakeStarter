# SDL2 + cMake Starter Proj Template
Just my own template project for Windows systems using some common useful libraries.

# Build requirements
Ensure the following are isntalled on your system:
- [Ninja build system](https://ninja-build.org/) - Not strictly necessary but it makes builds significantly faster (totally worth it)
- [Just command runner must be installed](https://github.com/casey/just)
- [CMake must be installed](https://cmake.org/download/)
- Visual Studio / MSVC compiler

Make sure these apps are in your environment variables.

# Building

Attempt to install dependencies automatically using chocolatey:
```
powershell .\support\install_deps.ps1
```
Once cMake, Just & Ninja is installed and they are in your `$PATH` environment vars, you can run the rest
```
just vswhere
just build
```
# Vendor libs

My common useful libraries are included:
```
vendor (30.57 MiB)
├─ dylib (29.10 KiB)
├─ magic_enum (60.35 KiB)
├─ copper (83.50 KiB)
├─ hashlib (149.51 KiB)
├─ concurrentqueue (234.12 KiB)
├─ asyncpp (458.24 KiB)
├─ parallel_hashmap (634.32 KiB)
├─ json (785.28 KiB)
├─ spdlog (837.39 KiB)
├─ tracy (1.35 MiB)
├─ sqlite342 (10.08 MiB)
└─ duckdb (15.94 MiB)
```

## Compile_commands.json
In powershell:
```
just clang
```

## Useful commands

- `just fmt` : Formats `src/` dir
- `just export` : Generates a zip file of the project
- `just build` : Builds the project
- `just clean` : Cleans the project
- `just wt` : Opens the newer Windows Terminal wt.exe
- `just stats` : Runs code stats using [Tokei](https://github.com/XAMPPRocky/tokei)

### Todo
-  When generating an export zip file, all the `*.lib` libraries are archived aswell. For some reason powershell wont let me only archive the nested `/lib/sdl2` folder by itself.
