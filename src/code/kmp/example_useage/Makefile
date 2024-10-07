#Written by Vito(DevVitoP)

example_file := ./kmp_example.c
delete := rm -f

kmp_dll := .

.PHONY : all clean
all : $(example_file) $(kmp_dll)/kmp.dll
	gcc $(example_file) -o $(example_file).exe -L $(kmp_dll) -lkmp

clean : 
	-$(delete) $(example_file).exe


