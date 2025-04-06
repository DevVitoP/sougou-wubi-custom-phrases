#Written by Vito(DevVitoP)

kmp_path := ./kmp.c
kmp_header_path := ./kmp.h
kmp_dll := ./kmp.dll

.PHONY : all

all : $(kmp_dll)

$(kmp_dll) : $(kmp_path) $(kmp_header_path)
	gcc -shared $< -o $@
