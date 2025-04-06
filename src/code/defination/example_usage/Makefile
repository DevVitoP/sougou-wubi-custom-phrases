#Written by Vito
example_code := ./all_examples.c
header := ./statement.h
example_exe := ./example.exe

def_dll := ./defination.dll

delete := rm -f

.PHONY : all clean

all : $(example_exe)

$(example_exe) : $(example_code) $(header)
	gcc $< -o $@ -L . -ldefination

clean :
	-$(delete) $(example_exe)
