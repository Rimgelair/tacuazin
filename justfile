set windows-shell := ["pwsh.exe", "-NoLogo", "-Command"]

build_dir := "build"
binary_name := "iruc.exe"

config:
    @cmake -B {{ build_dir }} -G Ninja

build:
    @cmake --build {{ build_dir }}

clean:
    @Remove-Item {{ build_dir }}

run: build
    @./{{ build_dir }}/{{ binary_name }}
    
rebuild: clean config
