#Written by Vito(DevVitoP)

example_file := ./message_window_example.c
example_header := ./message_window.h

message_window_dll := .

delete := rm -f

.PHONY : all clean

all : $(example_file) $(example_header) $(message_window_dll)/message_window.dll
	gcc $< -o $<.exe -L $(message_window_dll) -lmessage_window -mwindows

clean :
	-$(delete) $(example_file).exe
