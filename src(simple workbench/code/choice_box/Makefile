#Written by Vito
choice_box_code := ./choice_box.c
choice_box_header := ./choice_box.h

gen_choice_box_dll := ./choice_box.dll

delete := rm -f

.PHONY : all clean

all : $(gen_choice_box_dll)

$(gen_choice_box_dll) : $(choice_box_code) $(choice_box_header)
	gcc -shared $< -o $@ -lshell32 -lcomdlg32 -lole32

clean : 
	-$(delete) $(gen_choice_box_dll)
