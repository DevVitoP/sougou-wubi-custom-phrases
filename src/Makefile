#Written by Vito

build_dir := ./code/build

VPATH := $(build_dir)
makefile_build := Makefile
exe_name := $(build_dir)/main.exe
mv_pos := .

.PHONY : all
all : $(makefile_build)
	make --directory $(build_dir) -f $(makefile_build)
	make --directory $(build_dir) -f $(makefile_build) clean
	mv $(exe_name) .
