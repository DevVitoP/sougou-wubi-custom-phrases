source_code_path :=  ./src/code
output_path := .

res_code := resource.rc
lib_code := defination.c
main_code := c.code.c

lib_name := defination
res_name := resource.res
exe_name := c.pgm.exe

delete := rm -f

.PHONY : all clean

all : $(output_path)/$(exe_name)
	$(delete) $(output_path)/$(res_name)
	$(delete) $(output_path)/lib$(lib_name).a
	$(delete) $(output_path)/lib$(lib_name).a.o


#c.pgm.exe
Target_obj := $(source_code_path)/$(main_code) $(output_path)/$(res_name)
Target_lib := $(output_path)/lib$(lib_name).a

$(output_path)/$(exe_name) : $(Target) $(Target_lib)
	gcc $(Target_obj) -o $@ -L$(output_path) -l$(lib_name) -lcomdlg32 -lshell32 -lole32 -static

#resource.res
$(output_path)/$(res_name) : $(source_code_path)/$(res_code)
	windres.exe $< -O coff -o $@

#libdefination.a.o
$(output_path)/lib$(lib_name).a.o : $(source_code_path)/$(lib_code)
	gcc -c $< -o $@

#libdefination.a
$(output_path)/lib$(lib_name).a : $(output_path)/lib$(lib_name).a.o
	ar rcs $@ $<

clean :
	$(delete) $(output_path)/$(exe_name) 


