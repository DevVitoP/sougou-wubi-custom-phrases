#Written by Vito

build_choice_box := ./build_choice_box.c
bcb_obj := ./build_choice_box.o

build_message_window := ./build_message_window.c
bmw_obj := ./build_message_window.o

build_kmp := ./build_kmp.c
bk_obj := ./build_kmp.o

build_defination := ./build_defination.c
bd_obj := ./build_defination.o

build_default_main := ./build_default_main.c
bdm_obj := ./build_default_main.o

rc := ./source/resource.rc
res := ./resource.res

main := ./main.c
main_exe := ./main.exe

delete := rm -f
CC := gcc
RC := windres

.PHONY : all clean
all : $(main_exe)

$(main_exe) : $(main) $(res) $(bcb_obj) $(bmw_obj) $(bk_obj) $(bd_obj) $(bdm_obj)
	$(CC) $^ -o $@ -luser32 -lkernel32 -lgdi32 \
		-lshell32 -lcomdlg32 -lole32 \
		-mwindows


%.o : %.c
	$(CC) -c $< -o $@

$(res) : $(rc)
	$(RC) --output-format=coff -i $< -o $@

clean :
	-$(delete) $(res) 
	-$(delete) $(bcb_obj)
	-$(delete) $(bmw_obj)
	-$(delete) $(bk_obj)
	-$(delete) $(bd_obj)
	-$(delete) $(bdm_obj)




