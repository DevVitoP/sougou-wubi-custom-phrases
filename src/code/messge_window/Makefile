#Written by Vito(DevVitoP)

mw_path := ./message_window.c
mwh_path := ./message_window.h
rc_path := ./resource.rc

res_path := ./resource.res
obj_dll_path := ./message_window.dll

delete := rm -f

.PHONY : all clean

all : $(obj_dll_path)
	-$(delete) $(res_path)

$(res_path) : $(rc_path)
	windres --output-format=coff -i $< -o $@

$(obj_dll_path) :  $(mw_path) $(mwh_path) $(res_path)
	gcc -shared $< $(res_path) -o $(obj_dll_path) -luser32 -lkernel32 -lgdi32

clean:
	-$(delete) $(obj_dll_path)
