#Written by Vito
defination_code := ./defination.c
defination_header := ./statement.h

defination_dll := ./defination.dll
delete := rm -f

.PHONY : all clean

all : $(defination_dll)

$(defination_dll) : $(defination_code) $(defination_header)
	gcc -shared $< -o $@

clean :
	-$(delete) $(defination_dll)
